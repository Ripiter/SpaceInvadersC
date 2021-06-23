#include "Bullet.h"

bool iterate_bullet_move(void* data)
{
	Bullet_t* bullet = data;
	bullet->bulletPos->x--;

	return TRUE;
}

void free_bullet_data(void* data)
{
	Bullet_t* bullet = data;
	free(bullet->bulletPos);
	free(bullet);
}

Bullet_t* init_bullet(int _x, int _y)
{
	Bullet_t* b = malloc(sizeof(Bullet_t));

	b->bulletPos = init_vector(_x, _y);
	b->bulletChar = 'I';

	return b;
}
