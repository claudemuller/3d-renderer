#ifndef INC_3DRENDERER_TRIANGLE_H
#define INC_3DRENDERER_TRIANGLE_H

#include "vector.h"

typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
	vec2_t points[3];
} triangle_t;

#endif //INC_3DRENDERER_TRIANGLE_H
