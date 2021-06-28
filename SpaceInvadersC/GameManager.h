#pragma once
#include "Map.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Utility/List.h"
#include "Entities/Bullet.h"

#define clear() printf("\033[H\033[J");

typedef struct GameManager {

	int gameOver;
	Map_t* map;
	list* enemies;
	list* enemyBullets;
	Player_t* player;
	int updateMap;
}GameManager_t;


void init_game(GameManager_t* gameManager);
int enemy_shoot(GameManager_t* game, unsigned int tick);
void init_enemies(GameManager_t* game);
void place_entities(GameManager_t* game);
void game_update(GameManager_t* gameManager, unsigned int tick);
int check_for_collision(GameManager_t* game);
void destroy_game(GameManager_t* gameManager);
void check_game_over(GameManager_t* game);