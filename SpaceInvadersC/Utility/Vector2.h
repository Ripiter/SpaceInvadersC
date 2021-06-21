#pragma once

typedef struct Vector2 Vector2_t;


struct Vector2 {
	int x;
	int y;
};

Vector2_t* init_vector(int _x, int _y);
int vector_equals(Vector2_t *_vec1, Vector2_t *_vec2);