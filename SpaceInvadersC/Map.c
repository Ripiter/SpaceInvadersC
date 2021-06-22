#include "Map.h"

void init_map(Map_t* _map)
{	
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			Vector2_t pos;
			pos.x = i;
			pos.y = j;

			_map->map[i][j].fieldPos.x = i;
			_map->map[i][j].fieldPos.y = j;
			_map->map[i][j].fieldChar = 'X';
		}
	}

}

void print_map(Map_t* _map)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			printf("%c", _map->map[i][j].fieldChar);
		}
		printf("\n");
	}
}
