#include "Vector2.h"
#include <stdlib.h>
#include <stdio.h>


Vector2_t* init_vector(int _x, int _y)
{
	Vector2_t* v = malloc(sizeof(Vector2_t));

	if (v == 0){
		printf("Erorr creaing new vector");
		return 0;
	}

	v->x = _x;
	v->y = _y;
	return v;
}

