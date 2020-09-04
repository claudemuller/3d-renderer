#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

//const int N_POINTS = 9 * 9 * 9;
const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
int fov_factor = 640;
vec3_t camera_position = {0, 0, -5};
vec3_t cube_rotation = {0, 0, 0};

bool is_running = NULL;

void setup(void);

void process_input(void);

void update(void);

void render(void);

void print_bench(void);

int main(void) {
	is_running = init_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

//	print_bench();

	cleanup();

	return 0;
}

void setup(void) {
	// Allocate the required bytes in memory for the colour buffer.
	colour_buffer = (uint32_t *) malloc(sizeof(uint32_t) * window_width * window_height);

	colour_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			window_width,
			window_height
	);

	int c = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = {x, y, z};
				cube_points[c++] = new_point;
			}
		}
	}
}

vec2_t project(vec3_t point) {
	return (vec2_t) {
		.x = fov_factor * point.x / point.z,
		.y = fov_factor * point.y / point.z
	};
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
	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;

	for (int i = 0; i < N_POINTS; i++) {
		// Get point.
		vec3_t point = cube_points[i];

		// Rotate point.
		vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
		transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

		// Translate the points away from the camera.
		transformed_point.z -= camera_position.z;

		// Create the projected point.
		vec2_t projected_point = project(transformed_point);

		projected_points[i] = projected_point;
	}
}

void render(void) {
	draw_grid();

	for (int i = 0; i < N_POINTS; i++) {
		draw_fill_rect(
				projected_points[i].x + window_width / 2,
				projected_points[i].y + window_height / 2,
				4,
				4,
				PINK);
	}

	render_colour_buffer();
	clear_colour_buffer(BLACK);

	SDL_RenderPresent(renderer);
}
