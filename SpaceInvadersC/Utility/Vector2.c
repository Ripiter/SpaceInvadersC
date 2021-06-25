#include "Vector2.h"
#include <stdlib.h>
#include <stdio.h>


Vector2_t* init_vector(int _x, int _y)
{
	Vector2_t* v = malloc(sizeof(Vector2_t));

	if (v == 0) {
		printf("Erorr creaing new vector");
		return 0;
	}

	v->x = _x;
	v->y = _y;
	return v;
}

int vector_equals(Vector2_t* _vec1, Vector2_t* _vec2) {

	if (_vec1->x == _vec2->x && _vec1->y == _vec2->y)
		return 1;

	return 0;
}