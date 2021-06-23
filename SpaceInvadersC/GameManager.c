#include "GameManager.h"

void init_game(GameManager_t* gameManager)
{
	gameManager->map = NULL;
	gameManager->player = NULL;
	gameManager->gameOver = 0;
	gameManager->updateMap = 0;

	gameManager->map = malloc(sizeof(Map_t));
	gameManager->enemies = malloc(sizeof(list));
	gameManager->bullets = malloc(sizeof(list));

	init_enemies(gameManager);
	list_new(gameManager->bullets, sizeof(Bullet_t), free_bullet_data);

	gameManager->map = init_map();
	gameManager->player = init_player(MAP_HEIGHT - 1, MAP_WIDTH / 2);

	gameManager->player->map = gameManager->map;

	place_on_map(gameManager->map, gameManager->player->playerPos, gameManager->player->playerChar);
	take_place_map(gameManager->map, gameManager->player, 1);

	place_entities(gameManager);

	print_map(gameManager->map);
}

void init_enemies(GameManager_t* game) {
	list_new(game->enemies, sizeof(Enemy_t), free_enemy_data);
	/*
	 XXXXXX
	  XXXX
	   XX
	*/

	list_append(game->enemies, init_enemy(1, 0, 3));
	list_append(game->enemies, init_enemy(1, 0, 4));
	list_append(game->enemies, init_enemy(1, 0, 5));
	list_append(game->enemies, init_enemy(1, 0, 6));
	list_append(game->enemies, init_enemy(1, 0, 7));
	list_append(game->enemies, init_enemy(1, 0, 8));


	list_append(game->enemies, init_enemy(1, 1, 4));
	list_append(game->enemies, init_enemy(1, 1, 5));
	list_append(game->enemies, init_enemy(1, 1, 6));
	list_append(game->enemies, init_enemy(1, 1, 7));

	list_append(game->enemies, init_enemy(1, 2, 5));
	list_append(game->enemies, init_enemy(1, 2, 6));
}

void place_entities(GameManager_t* game)
{
	for (int i = 0; i < list_size(game->enemies); i++)
	{
		Enemy_t* e = list_at(game->enemies, i);
		place_on_map(game->map, e->pos, e->enemyChar);
	}
	for (int i = 0; i < list_size(game->bullets); i++)
	{
		Bullet_t* b = list_at(game->bullets, i);
		place_on_map(game->map, b->bulletPos, b->bulletChar);
	}
}

void game_update(GameManager_t* gameManager)
{
	gameManager->updateMap += player_update(gameManager->player);

	if (get_button_down(Q)) {
		list_for_each(gameManager->enemies, iterate_enemy_move);
		list_for_each(gameManager->bullets, iterate_bullet_move);
		gameManager->updateMap += 1;
	}

	if (get_button_down(E)) {
		list_append(gameManager->bullets, init_bullet(gameManager->player->playerPos->x - 2, gameManager->player->playerPos->y));
		gameManager->updateMap += 1;
	}



	if (gameManager->updateMap != 0) {
		clean_map(gameManager->map);
		place_entities(gameManager);
		clear();

		print_map(gameManager->map);
		gameManager->updateMap = 0;
	}
}

void destroy_game(GameManager_t* gameManager)
{
	free(gameManager->map);
	list_destroy(gameManager->enemies);
	list_destroy(gameManager->bullets);
	destroy_player(gameManager->player);
	free(gameManager);
}
