#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int window_width = 800;
int window_height = 600;
bool is_running = NULL;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *colour_buffer_texture = NULL;

// Declare a pointer to an array of uint32 elements.
uint32_t *colour_buffer = NULL;

bool init_window(void);
void setup(void);
void clear_colour_buffer(uint32_t colour);
void draw_grid(void);
void process_input(void);
void update(void);
void render(void);
void cleanup(void);

int main(void) {
    is_running = init_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    cleanup();

    return 0;
}

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "An error occurred: %s\n", SDL_GetError());
        return false;
    }

    // Set width and height to full screen resolution.
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;

    // Create SDL window.
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "An error occurred creating SDL window: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL renderer.
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "An error occurred creating SDL renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void setup(void) {
    // Allocate the required bytes in memory for the colour buffer
    colour_buffer = (uint32_t *) malloc(sizeof(uint32_t) * window_width * window_height);

    colour_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
    );
}

void clear_colour_buffer(uint32_t colour) {
    // y is the row.
    for (int y = 0; y < window_height; y++) {
        // x is the col.
        for (int x = 0; x < window_width; x++) {
            // Change position at x,y but convert 2D coord to 1D array idx.
            colour_buffer[(window_width * y) + x] = colour;
        }
    }
}

void render_colour_buffer(void) {
    SDL_UpdateTexture(colour_buffer_texture, NULL, colour_buffer, (int) (window_width * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, colour_buffer_texture, NULL, NULL);
}

void draw_grid(void) {
    int grid_size = 10;
    uint32_t grid_colour = 0x00000000;
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (y % grid_size == 0 || x % grid_size == 0) {
                colour_buffer[(window_width * y) + x] = grid_colour;
            }
        }
    }
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
        default:
            break;
    }
}

void update(void) {
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid();

    render_colour_buffer();
    clear_colour_buffer(0xFFFFFF00);

    SDL_RenderPresent(renderer);
}

void cleanup(void) {
    free(colour_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}