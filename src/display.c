#include "display.h"

int window_width = 800;
int window_height = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *colour_buffer_texture = NULL;
uint32_t *colour_buffer = NULL;

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
			SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP
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
	uint32_t grid_colour = DARK_GREY;
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			colour_buffer[(window_width * y) + x] = grid_colour;
		}
	}
}

void draw_pixel(int x, int y, uint32_t colour) {
	if (x > 0 && x < window_width && y > 0 && y < window_height) {
		colour_buffer[(window_width * y) + x] = colour;
	}
}

void draw_fill_rect(int x, int y, int width, int height, uint32_t colour) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			draw_pixel(current_x, current_y, colour);
		}
	}
}

void cleanup(void) {
	free(colour_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
