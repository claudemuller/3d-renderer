#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../array.h"
#include "../vector.h"
#include "../mesh.h"

#define MAX_MESH_FILE_LINE 1024

void parse_vertices(char* str);
void parse_faces(char* str);
char** split_string(char* str, char* delimiter);

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

char** split_string(char* str, char* delimiter) {
	char** segs = NULL;
	char* token = strtok(str, delimiter);
	while (token != NULL) {
		array_push(segs, token);
		token = strtok(NULL, " ");
	}
	return segs;
}
