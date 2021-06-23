#pragma once
#include "../Utility/Vector2.h"
#include "../Utility/List.h"

typedef struct {
	Vector2_t* bulletPos;
	char bulletChar;
}Bullet_t;

bool iterate_bullet_move(void* data);
void free_bullet_data(void* data);
Bullet_t* init_bullet(int _x, int _y);