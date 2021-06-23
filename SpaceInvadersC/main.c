#include "Utility/Vector2.h"
#include "Entities/Enemy.h"
#include "Map.h"
#include "Entities/Player.h"
#include "GameManager.h"

int main() {
	GameManager_t* game = malloc(sizeof(GameManager_t));
	init_game(game);

	//init_map(map);
	//print_map(map);
	int esc = 1;
	while (esc) {

		update_input();

		if (get_button_down(ESCAPE)) {
			esc = 0;
			printf("escape");
		}

		game_update(game);
	}

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