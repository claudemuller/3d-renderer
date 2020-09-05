#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"

//const int N_POINTS = 9 * 9 * 9;
//const int N_POINTS = 9 * 9 * 9;
//vec3_t cube_points[N_POINTS];
//vec2_t projected_points[N_POINTS];

int fov_factor = 640;
vec3_t camera_position = {0, 0, -5};
vec3_t cube_rotation = {0, 0, 0};
triangle_t triangles_to_render[N_MESH_FACES];

bool is_running = NULL;
int last_frame_time = 0;

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
	colour_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

	colour_buffer_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			window_width,
			window_height
	);

//	int c = 0;
//	for (float x = -1; x <= 1; x += 0.25) {
//		for (float y = -1; y <= 1; y += 0.25) {
//			for (float z = -1; z <= 1; z += 0.25) {
//				vec3_t new_point = {x, y, z};
//				cube_points[c++] = new_point;
//			}
//		}
//	}
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
	int waited_for = SDL_GetTicks();
	// Sleep the execution until the target time in milliseconds is reached.
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	// Only call delay if processing is too fast in the current frame.
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}
//	printf("FPS: %d\n", last_frame_time - waited_for);
	float delta_time = (float) (SDL_GetTicks() - last_frame_time) / 1000.0f;
	// Clamp deltaTime to a maximum value
//	delta_time = delta_time > 0.05f ? 0.05f : delta_time;
	// Sets the new ticks fo the current frame to be used in the next pass
	last_frame_time = SDL_GetTicks();

	cube_rotation.x += 0.5 * delta_time;
	cube_rotation.y += 0.5 * delta_time;
	cube_rotation.z += 0.5 * delta_time;

//	for (int i = 0; i < N_POINTS; i++) {
//		// Get point.
//		vec3_t point = cube_points[i];
//
//		// Rotate point.
//		vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
//		transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
//		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);
//
//		// Translate the points away from the camera.
//		transformed_point.z -= camera_position.z;
//
//		// Create the projected point.
//		vec2_t projected_point = project(transformed_point);
//
//		projected_points[i] = projected_point;
//	}

	// Loop all mesh faces.
	for (int i = 0; i < N_MESH_FACES; i++) {
		face_t mesh_face = mesh_faces[i];

		vec3_t face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];

		triangle_t projected_triangle;

		// Loop all three vertices of current face and apply transformation.
		for (int j = 0; j < 3; j++) {
			vec3_t transformed_vertex = face_vertices[j];

			// Rotate.
			transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
			transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

			// Translate the points away from the camera.
			transformed_vertex.z -= camera_position.z;

			// Create the projected point.
			vec2_t projected_point = project(transformed_vertex);

			// Scale and translate projected point to middle of screen.
			projected_point.x += window_width / 2;
			projected_point.y += window_height / 2;

			projected_triangle.points[j] = projected_point;
		}

		triangles_to_render[i] = projected_triangle;
	}
}

void render(void) {
	draw_grid();

//	for (int i = 0; i < N_POINTS; i++) {
//		draw_fill_rect(
//				projected_points[i].x + window_width / 2,
//				projected_points[i].y + window_height / 2,
//				4,
//				4,
//				PINK);
//	}

	// Loop over projected triangles and render them.
	for (int i = 0; i < N_MESH_FACES; i++) {
		triangle_t triangle = triangles_to_render[i];

		// Draw vertex points.
		draw_fill_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, PINK);
		draw_fill_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, PINK);
		draw_fill_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, PINK);

		// Draw unfilled triangle.
		draw_triangle(
				triangle.points[0].x, triangle.points[0].y,
				triangle.points[1].x, triangle.points[1].y,
				triangle.points[2].x, triangle.points[2].y,
				PINK
				);
	}

	render_colour_buffer();
	clear_colour_buffer(BLACK);

	SDL_RenderPresent(renderer);
}
