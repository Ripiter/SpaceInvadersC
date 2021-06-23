#include "Map.h"
#include <stdlib.h>
Map_t* init_map()
{	
	Map_t* map = malloc(sizeof(Map_t));

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			map->map[i][j].fieldPos.x = i;
			map->map[i][j].fieldPos.y = j;
			map->map[i][j].fieldChar = ' ';
			map->map[i][j].taken = 0;
		}
	}
	return map;
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

void clean_map(Map_t* _map)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if(_map->map[i][j].taken == 0)
				_map->map[i][j].fieldChar = ' ';
		}
	}
}

void take_place_map(Map_t* _map, Vector2_t* pos, int _taken)
{
	_map->map[pos->x][pos->y].taken = _taken;
}

void place_on_map(Map_t* _map, Vector2_t* pos, char _char)
{
	_map->map[pos->x][pos->y].fieldChar = _char;
	//_map->map[pos->x][pos->y].taken = 1;

}
