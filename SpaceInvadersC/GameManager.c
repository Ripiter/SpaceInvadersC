#include "GameManager.h"

void init_game(GameManager_t* gameManager)
{
	gameManager->map = NULL;
	gameManager->player = NULL;
	gameManager->gameOver = 0;
	gameManager->updateMap = 0;

	gameManager->map = malloc(sizeof(Map_t));
	gameManager->enemies = malloc(sizeof(list));
	gameManager->enemyBullets = malloc(sizeof(list));
	list_new(gameManager->enemyBullets, sizeof(Bullet_t), free_bullet_data);
	init_enemies(gameManager);

	gameManager->map = init_map();
	gameManager->player = init_player(MAP_HEIGHT - 1, MAP_WIDTH / 2);

	place_on_map(gameManager->map, gameManager->player->playerPos, gameManager->player->playerChar);

	place_entities(gameManager);

	print_map(gameManager->map);
}

int enemy_shoot(GameManager_t* game, unsigned int tick)
{
	if ((tick % 30) == 0)
	{
		for (int i = 0; i < list_size(game->enemies); i++)
		{
			Enemy_t* e = list_at(game->enemies, i);

			if(e->isHead == 1)
				list_append(game->enemyBullets, init_bullet(e->pos->x, e->pos->y));
		}
	}
	return 0;
}

void game_update(GameManager_t* gameManager, unsigned int tick)
{
	gameManager->updateMap += player_update(gameManager->player);
	// check if bullet was spawned on enemy
	gameManager->updateMap += check_for_collision(gameManager);

	gameManager->updateMap += enemy_shoot(gameManager, tick);

	// move enemy every 10 ticks
	if (tick % 20 == 0) {
		list_for_each(gameManager->enemies, iterate_enemy_move);
		gameManager->updateMap += 1;
		check_for_collision(gameManager);
	}

	if (tick % 2 == 0) {
		list_for_each(gameManager->player->bullets, iterate_bullet_move);
		list_for_each(gameManager->enemyBullets, iterate_enemy_bullet_move);
		gameManager->updateMap += 1;
	}

	if (gameManager->updateMap != 0) {
		check_for_collision(gameManager);
		clean_map(gameManager->map);
		place_entities(gameManager);
		clear();

		print_map(gameManager->map);
		gameManager->updateMap = 0;
	}

}

int check_for_collision(GameManager_t* game)
{
	int update = 0;
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
					bulletIndex += list_size(game->player->bullets);
					update = 1;
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

	// check if the bullet go the the end 
	// and remove it if it did
	for (int i = 0; i < list_size(game->player->bullets); i++)
	{
		Bullet_t* b = list_at(game->player->bullets, i);
		// check if the bullet got to the end
		if (b != NULL) {
			if (b->bulletPos != NULL) {
				if (b->bulletPos->x == 0) {
					list_remove_at(game->player->bullets, i);
					update = 1;
				}
			}
		}
	}

	for (int i = 0; i < list_size(game->enemyBullets); i++)
	{
		Bullet_t* bullet = list_at(game->enemyBullets, i);

		if (vector_equals(bullet->bulletPos, game->player->playerPos) == 1) {
			game->gameOver = 1;
		}

		if (bullet != NULL) {
			if (bullet->bulletPos != NULL) {
				if (bullet->bulletPos->x == MAP_HEIGHT) {
					list_remove_at(game->enemyBullets, i);
					update = 1;
				}
			}
		}
	}

	return update;
}

void destroy_game(GameManager_t* gameManager)
{
	free(gameManager->map);
	list_destroy(gameManager->enemies);
	list_destroy(gameManager->enemyBullets);
	destroy_player(gameManager->player);
	free(gameManager);
}

void check_game_over(GameManager_t* game)
{
	if (list_size(game->enemies) == 0)
		game->gameOver = 2;
	
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

	for (int i = 0; i < list_size(game->enemyBullets); i++)
	{
		Bullet_t* b = list_at(game->enemyBullets, i);
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

	list_prepend(game->enemies, init_enemy(0, 1, 1, 3));

	list_prepend(game->enemies, init_enemy(0, 1, 1, 4));
	list_prepend(game->enemies, init_enemy(0, 1, 1, 5));
	list_prepend(game->enemies, init_enemy(0, 1, 1, 6));
	list_prepend(game->enemies, init_enemy(0, 1, 1, 7));
	list_prepend(game->enemies, init_enemy(0, 1, 1, 8));


	list_prepend(game->enemies, init_enemy(0, 1, 2, 4));
	list_prepend(game->enemies, init_enemy(0, 1, 2, 5));
	list_prepend(game->enemies, init_enemy(0, 1, 2, 6));
	list_prepend(game->enemies, init_enemy(0, 1, 2, 7));

	list_prepend(game->enemies, init_enemy(0, 1, 3, 5));
	list_prepend(game->enemies, init_enemy(1, 1, 3, 6));
}