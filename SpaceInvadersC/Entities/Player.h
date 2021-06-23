#pragma once
#include "../Utility/Vector2.h"
#include <stdlib.h>
#include "../Utility/Input.h"
#include "../Map.h"

#define LEFT 75
#define RIGHT 77 
#define UP 72
#define DOWN 80

typedef struct Player {
	Vector2_t* playerPos;
	char playerChar;
	Map_t* map;
}Player_t;


Player_t* init_player(int _x, int _y);
void destroy_player(Player_t* player);
int player_update(Player_t* player);