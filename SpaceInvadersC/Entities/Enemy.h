#pragma once
#include "../Utility/Vector2.h"
#include "../Utility/List.h"

typedef struct {
	int hp;
	Vector2_t* pos;
}Enemy_t;

Enemy_t* init_enemy(int _hp, int _x, int _y);

void free_enemy_data(void* data);


bool iterate_enemy_dmg(void* data);

bool iterate_enemy_print(void* data);
