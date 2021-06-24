#include "GameManager.h"

void init_game(GameManager_t* gameManager)
{
	gameManager->map = NULL;
	gameManager->player = NULL;
	gameManager->gameOver = 0;
	gameManager->updateMap = 0;

	gameManager->map = malloc(sizeof(Map_t));
	gameManager->enemies = malloc(sizeof(list));


	init_enemies(gameManager);

	gameManager->map = init_map();
	gameManager->player = init_player(MAP_HEIGHT - 1, MAP_WIDTH / 2);


	place_on_map(gameManager->map, gameManager->player->playerPos, gameManager->player->playerChar);


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
	for (int i = 0; i < list_size(game->player->bullets); i++)
	{
		Bullet_t* b = list_at(game->player->bullets, i);
		place_on_map(game->map, b->bulletPos, b->bulletChar);
	}

	place_on_map(game->map, game->player->playerPos, game->player->playerChar);
}

void game_update(GameManager_t* gameManager)
{
	// this is for testing in later phase this will be removed
	gameManager->updateMap += player_update(gameManager->player);

	// this is for testing in later phase this will be removed
	if (get_button_down(Q)) {
		list_for_each(gameManager->enemies, iterate_enemy_move);
		list_for_each(gameManager->player->bullets, iterate_bullet_move);
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
	destroy_player(gameManager->player);
	free(gameManager);
}
