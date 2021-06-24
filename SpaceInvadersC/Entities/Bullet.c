#include "Bullet.h"
#include "../Map.h"

bool iterate_bullet_move(void* data)
{
	Bullet_t* bullet = data;
	
	if (out_of_bounds(bullet->bulletPos->x - 1, bullet->bulletPos->y) == 0) {
		bullet->bulletPos->x--;
	}

	return TRUE;
}

void free_bullet_data(void* data)
{
	Bullet_t* bullet = data;
	free(bullet->bulletPos);
	free(bullet);


	bullet->bulletPos = NULL;
	bullet = NULL;
}

Bullet_t* init_bullet(int _x, int _y)
{
	Bullet_t* b = malloc(sizeof(Bullet_t));

	b->bulletPos = init_vector(_x, _y);
	b->bulletChar = 'I';

	return b;
}
