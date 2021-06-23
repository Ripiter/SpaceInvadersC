#include "Player.h"
#include <stdio.h>
Player_t* init_player(int _x, int _y)
{
	Player_t* p = malloc(sizeof(Player_t));

	p->playerPos = init_vector(_x, _y);
	p->playerChar = 'O';

	return p;
}

void destroy_player(Player_t* player)
{
	free(player->playerPos);
	free(player);
}

int update = 0;
int player_update(Player_t* player)
{
	update = 0;
	if (get_button_down(LEFT)) {
		if (player->playerPos->y > 0) {
			take_place_map(player->map, player->playerPos, 0);
			player->playerPos->y -= 1;
			update = 1;
		}
		//printf("down\n");
	}
	if (get_button_down(RIGHT)) {
		take_place_map(player->map, player->playerPos, 0);
		player->playerPos->y += 1;
		//printf("Up\n");
		update = 1;
	}
	if (get_button_down(DOWN)) {
		take_place_map(player->map, player->playerPos, 0);
		player->playerPos->x += 1;
		//printf("right\n");
		update = 1;
	}
	if (get_button_down(UP)) {
		if (player->playerPos->x > 0) {
			take_place_map(player->map, player->playerPos, 0);
			player->playerPos->x -= 1;
			//printf("left\n");
			update = 1;
		}
	}

	if (update > 0) {
		place_on_map(player->map, player->playerPos, player->playerChar);
	}

	return update;
}

