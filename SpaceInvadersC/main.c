#include <stdio.h>
#include <stdlib.h>
#include "Utility/Vector2.h"
#include "Utility/List.h"

typedef struct {
	int hp;
	Vector2_t* pos;
}Enemy_t;

bool iterate_enemy_dmg(void* data) {
	Enemy_t* enemy = data;
	enemy->hp -= 30;
	return TRUE;
}

bool iterate_enemy_print(void* data) {
	Enemy_t* enemy = data;
	printf("HP: %d\n", enemy->hp);
	return TRUE;
}


Enemy_t* init_enemy(int _hp, int _x, int _y) {
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

	free(data);
}


int main() {
	Enemy_t* e1 = init_enemy(100, 69, 68);
	Enemy_t* e2 = init_enemy(90, 99, 98);


	list* enemies = malloc(sizeof(list));
	// set freefunction to null if the items do not special free
	list_new(enemies, sizeof(Enemy_t), free_enemy_data);

	list_append(enemies, e1);
	list_append(enemies, e2);
	list_append(enemies, init_enemy(10, 10, 10));

	//list_for_each(enemies, iterate_enemy_dmg);
	//list_for_each(enemies, iterate_enemy_print);


	//list_append(enemies, init_enemy(420, 360));
	//printf("added new enemy\n");
	//list_for_each(enemies, iterate_enemy_dmg);
	//list_for_each(enemies, iterate_enemy_print);


	for (int i = 0; i < list_size(enemies); i++)
	{
		Enemy_t* e = list_at(enemies, i);
		printf("Enemy hp: %d\n", e->hp);
	}


	list_destroy(enemies);


	return 0;
}


