#include <stdio.h>
#include <SDL2/SDL.h>

void init_window(void);

int main(void) {
    init_window();

    return 0;
}

void init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "An error occurred: %s\n", SDL_GetError());
        exit(1);
    }
}
