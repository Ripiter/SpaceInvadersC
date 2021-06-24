#pragma once
#include "../Utility/Vector2.h"
#include "../Utility/Input.h"
#include "../Utility/List.h"
#include "../Map.h"
#include "Bullet.h"
#include <stdlib.h>

#define LEFT 75
#define RIGHT 77 
#define UP 72
#define DOWN 80

typedef struct Player {
	Vector2_t* playerPos;
	char playerChar;
	list* bullets;
}Player_t;


Player_t* init_player(int _x, int _y);
void destroy_player(Player_t* player);
int player_update(Player_t* player);