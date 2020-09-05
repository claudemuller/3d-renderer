#ifndef INC_3DRENDERER_DISPLAY_H
#define INC_3DRENDERER_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "colours.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

extern int window_width;
extern int window_height;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *colour_buffer_texture;

// Declare a pointer to an array of uint32 elements.
extern uint32_t *colour_buffer;

bool init_window(void);
void render_colour_buffer(void);
void clear_colour_buffer(colour_t colour);
void draw_grid(void);
void draw_pixel(int x, int y, colour_t colour);
void draw_fill_rect(int x, int y, int width, int height, colour_t colour);
void draw_line(int x0, int y0, int x1, int y1, colour_t colour);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, colour_t colour);
void destroy_sdl(void);

#endif //INC_3DRENDERER_DISPLAY_H
