#include "Player.h"
#include <stdio.h>
Player_t* init_player(int _x, int _y)
{
	Player_t* p = malloc(sizeof(Player_t));
	p->bullets = malloc(sizeof(list));

	list_new(p->bullets, sizeof(Bullet_t), free_bullet_data);

	p->playerPos = init_vector(_x, _y);
	p->playerChar = 'O';

	return p;
}

void destroy_player(Player_t* player)
{
	list_destroy(player->bullets);
	free(player->playerPos);
	free(player);
}

int update = 0;
int player_update(Player_t* player)
{
	if (get_button_down(LEFT)) {
		if (player->playerPos->y > 0) {
			player->playerPos->y -= 1;
			update = 1;
		}
		//printf("down\n");
	}
	if (get_button_down(RIGHT)) {
		player->playerPos->y += 1;
		//printf("Up\n");
		update = 1;
	}
	if (get_button_down(DOWN)) {
		player->playerPos->x += 1;
		//printf("right\n");
		update = 1;
	}
	if (get_button_down(UP)) {
		if (player->playerPos->x > 0) {
			player->playerPos->x -= 1;
			//printf("left\n");
			update = 1;
		}
	}

	if (get_button_down(E)) {
		list_append(player->bullets, init_bullet(player->playerPos->x - 1, player->playerPos->y));
		update = 1;
	}

	return update;
}

