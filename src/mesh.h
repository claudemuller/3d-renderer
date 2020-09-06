#ifndef INC_3DRENDERER_MESH_H
#define INC_3DRENDERER_MESH_H

#include "vector.h"
#include "triangle.h"

#define MAX_MESH_FILE_LINE 1024

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) // 6 cube faces, 2 triangles per face.

extern vec3_t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];

typedef struct {
	vec3_t* vertices; // Dynamic array of vertices.
	face_t* faces;    // Dynamic array of faces.
	vec3_t rotation;  // Rotation with x, y, z
} mesh_t;

// Global mesh.
extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_obj_file_data(char* filename);
void parse_vertices(char* str);
void parse_faces(char* str);

#endif //INC_3DRENDERER_MESH_H
