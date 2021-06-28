#include "Utility/Vector2.h"
#include "Entities/Enemy.h"
#include "Map.h"
#include "Entities/Player.h"
#include "GameManager.h"

#include <Windows.h>
#include <time.h>

#define GetTime() GetTickCount()

int main() {
	GameManager_t* game = malloc(sizeof(GameManager_t));
	init_game(game);
	if (game == NULL)
		return -1;

	time_t t = time(NULL);
	//struct tm _nextLoop = *localtime(&t)->tm_sec;



	const double MS_PER_FRAME = 60;

	int esc = 1;
	unsigned int tick = 0;

	while (esc && game->gameOver == 0) {
		double start = localtime(&t)->tm_sec;

		update_input();

		if (get_button_down(ESCAPE)) {
			esc = 0;
			printf("escape");
		}

		game_update(game, tick);

		tick += 1;
		check_game_over(game);
		Sleep(start + MS_PER_FRAME + localtime(&t)->tm_sec);
	}
	clear();
	if (game->gameOver == 2) {
		printf("Game over, You won");
	}
	else {
		printf("Game over, You lost");
	}





	/*
	GameManager_t* game = malloc(sizeof(GameManager_t));
	init_game(game);
	if (game == NULL)
		return -1;

	int esc = 1;
	while (esc && game->gameOver == 0) {

		// create some kind of loop
		// with tick system

		update_input();

		if (get_button_down(ESCAPE)) {
			esc = 0;
			printf("escape");
		}

		game_update(game);
	}
	*/

	destroy_game(game);

	return 0;
}



/*
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
*/