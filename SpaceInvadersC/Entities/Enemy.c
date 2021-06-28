#include "Enemy.h"

Enemy_t* init_enemy(int _isHead, int _hp, int _x, int _y)
{
	Enemy_t* enemy = malloc(sizeof(Enemy_t));

	if (enemy == NULL)
		return NULL;

	enemy->hp = _hp;
	enemy->enemyChar = 'X';
	enemy->pos = init_vector(_x, _y);
	enemy->enemyDirection = 0;
	enemy->isHead = _isHead;

	return enemy;
}

void free_enemy_data(void* data)
{
	Enemy_t* enemy = data;

	free(enemy->pos);
	free(enemy);

	enemy->pos = NULL;
	enemy = NULL;
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

bool iterate_enemy_move(void* data)
{
	Enemy_t* enemy = data;
	// down
	//enemy->pos->x++;

	if (enemy->enemyDirection == 0) {
		enemy->pos->y--;
		enemy->enemyDirection = 1;
	}
	else if (enemy->enemyDirection == 1) {
		enemy->pos->y++;
		enemy->enemyDirection = 2;
	}	
	else if (enemy->enemyDirection == 2) {
		enemy->pos->y++;
		enemy->enemyDirection = 3;
	}
	else if (enemy->enemyDirection == 3) {
		enemy->pos->y--;
		enemy->enemyDirection = 4;
	}
	else if (enemy->enemyDirection == 4) {
		enemy->pos->x++;
		enemy->enemyDirection = 0;
	}
	// TODO: add movement for going left to right
	// and after a couple of ticks move 1 space forward

	// add a random chance to shoot a bullet

	return TRUE;
}
