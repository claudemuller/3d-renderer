#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int window_width = 800;
const int window_height = 600;

bool is_running = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
// Declare a pointer to an array of uint32 elements.
uint32_t *colour_buffer = NULL;
SDL_Texture *colour_buffer_texture = NULL;

bool init_window(void);

void setup(void);

void clear_colour_buffer(uint32_t colour);

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

    clear_colour_buffer(0xFFFFFF00);
    render_colour_buffer();

    SDL_RenderPresent(renderer);
}

void cleanup(void) {
    free(colour_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}