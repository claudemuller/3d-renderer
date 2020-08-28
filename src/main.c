#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init_window(void);
void cleanup(void);

int main(void) {
    is_running = init_window();

    cleanup();

    return 0;
}

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "An error occurred: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL window
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "An error occurred creating SDL window: %s\n", SDL_GetError());
        return false;
    }

    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "An error occurred creating SDL renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void cleanup(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}