#include "Enemy.h"

Enemy_t* init_enemy(int _hp, int _x, int _y)
{
	Enemy_t* enemy = malloc(sizeof(Enemy_t));

	if (enemy == NULL)
		return NULL;

	enemy->hp = _hp;
	enemy->pos = init_vector(_x, _y);

	return enemy;
}

void free_enemy_data(void* data)
{
	Enemy_t* enemy = data;

	free(enemy->pos);

	free((Enemy_t*)data);
}

bool iterate_enemy_dmg(void* data)
{
	Enemy_t* enemy = data;
	enemy->hp -= 30;
	return TRUE;
}

bool iterate_enemy_print(void* data)
{
	Enemy_t* enemy = data;
	printf("HP: %d\n", enemy->hp);
	return TRUE;
}
