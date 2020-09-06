#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "array.h"
#include "file.h"

mesh_t mesh = {
		.vertices = NULL,
		.faces = NULL,
		.rotation = {0, 0, 0}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
		{.x = -1, .y = -1, .z = -1}, // 1
		{.x = -1, .y =  1, .z = -1}, // 2
		{.x =  1, .y =  1, .z = -1}, // 3
		{.x =  1, .y = -1, .z = -1}, // 4
		{.x =  1, .y =  1, .z =  1}, // 5
		{.x =  1, .y = -1, .z =  1}, // 6
		{.x = -1, .y =  1, .z =  1}, // 7
		{.x = -1, .y = -1, .z =  1}  // 8
};

face_t cube_faces[N_CUBE_FACES] = {
		// Front.
		{.a = 1, .b = 2, .c = 3},
		{.a = 1, .b = 3, .c = 4},
		// Right.
		{.a = 4, .b = 3, .c = 5},
		{.a = 4, .b = 5, .c = 6},
		// Back.
		{.a = 6, .b = 5, .c = 7},
		{.a = 6, .b = 7, .c = 8},
		// Left.
		{.a = 8, .b = 7, .c = 2},
		{.a = 8, .b = 2, .c = 1},
		// Top.
		{.a = 2, .b = 7, .c = 5},
		{.a = 2, .b = 5, .c = 3},
		// Bottom.
		{.a = 6, .b = 8, .c = 1},
		{.a = 6, .b = 1, .c = 4}
};

void load_cube_mesh_data(void) {
	for (int i = 0; i < N_CUBE_VERTICES; i++) {
		vec3_t cube_vertex = cube_vertices[i];
		array_push(mesh.vertices, cube_vertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++) {
		face_t cube_face = cube_faces[i];
		array_push(mesh.faces, cube_face);
	}
}

void load_obj_file_data(char* filename) {
	FILE* fp;
	char line[MAX_MESH_FILE_LINE];

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
	}

	while (fgets(line, MAX_MESH_FILE_LINE, fp) != NULL) {
		// Parse vertices data into mesh.vertices.
		if (line[0] == 'v' && line[1] == ' ') {
			parse_vertices(line);
		}
		// Parse faces data into mesh.faces.
		if (line[0] == 'f' && line[1] == ' ') {
			parse_faces(line);
		}
	}

	fclose(fp);
}

void parse_vertices(char* str) {
	char** vertices = split_string(str, " ");
	if (array_length(vertices) > 3) {
		vec3_t vertex = {
				.x = atof(vertices[1]),
				.y = atof(vertices[2]),
				.z = atof(vertices[3])
		};
		array_push(mesh.vertices, vertex);
	}
	array_free(vertices);
}

void parse_faces(char* str) {
	char** faces = split_string(str, " ");
	if (array_length(faces) > 3) {
		face_t face = {
				.a = atoi(split_string(faces[1], "/")[0]),
				.b = atoi(split_string(faces[2], "/")[0]),
				.c = atoi(split_string(faces[3], "/")[0])
		};
		array_push(mesh.faces, face);
	}
	array_free(faces);
}
