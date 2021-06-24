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

void game_update(GameManager_t* gameManager)
{
	// this is for testing in later phase this will be removed
	gameManager->updateMap += player_update(gameManager->player);

	// this is for testing in later phase this will be removed
	if (get_button_down(Q_BTN)) {
		list_for_each(gameManager->enemies, iterate_enemy_move);
		gameManager->updateMap += 1;
	}
	list_for_each(gameManager->player->bullets, iterate_bullet_move);
	check_for_collision(gameManager);

	//if (gameManager->updateMap != 0) {
	check_for_collision(gameManager);
	clean_map(gameManager->map);
	place_entities(gameManager);
	clear();

	print_map(gameManager->map);
	gameManager->updateMap = 0;
	//}
}

void check_for_collision(GameManager_t* game)
{
	for (int enemyIndex = 0; enemyIndex < list_size(game->enemies); enemyIndex++)
	{
		Enemy_t* e = list_at(game->enemies, enemyIndex);
		for (int bulletIndex = 0; bulletIndex < list_size(game->player->bullets); bulletIndex++)
		{
			Bullet_t* b = list_at(game->player->bullets, bulletIndex);

			if (e != NULL && b != NULL) {

				if (vector_equals(e->pos, b->bulletPos) == 1) {	
					list_remove_at(game->enemies, enemyIndex);
					list_remove_at(game->player->bullets, bulletIndex);
				}
			}
			// check if the bullet got to the end
			if (b != NULL) {
				if (b->bulletPos != NULL) {
					if (b->bulletPos->x == 0) {
						list_remove_at(game->player->bullets, bulletIndex);
					}
				}
			}
		}

		// check if the enemy got to the end 
		if (e != NULL) {
			if (e->pos != NULL) {
				if (e->pos->x == MAP_HEIGHT) {
					list_remove_at(game->enemies, enemyIndex);
					game->gameOver = 1;
				}
			}
		}
	}
}

void destroy_game(GameManager_t* gameManager)
{
	free(gameManager->map);
	list_destroy(gameManager->enemies);
	destroy_player(gameManager->player);
	free(gameManager);
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

void init_enemies(GameManager_t* game) {
	list_new(game->enemies, sizeof(Enemy_t), free_enemy_data);
	/*
	 XXXXXX
	  XXXX
	   XX
	*/

	list_prepend(game->enemies, init_enemy(1, 1, 3));
	
	list_prepend(game->enemies, init_enemy(1, 1, 4));
	list_prepend(game->enemies, init_enemy(1, 1, 5));
	list_prepend(game->enemies, init_enemy(1, 1, 6));
	list_prepend(game->enemies, init_enemy(1, 1, 7));
	list_prepend(game->enemies, init_enemy(1, 1, 8));


	list_prepend(game->enemies, init_enemy(1, 2, 4));
	list_prepend(game->enemies, init_enemy(1, 2, 5));
	list_prepend(game->enemies, init_enemy(1, 2, 6));
	list_prepend(game->enemies, init_enemy(1, 2, 7));

	list_prepend(game->enemies, init_enemy(1, 3, 5));
	list_prepend(game->enemies, init_enemy(1, 3, 6));
}