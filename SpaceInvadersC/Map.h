#pragma once
#include "Field.h"
#include <stdio.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct Map Map_t;


struct Map {
	Field_t map[MAP_WIDTH][MAP_HEIGHT];
};

Map_t* init_map();
void print_map(Map_t* _map);
void clean_map(Map_t* _map);
void take_place_map(Map_t* _map, Vector2_t* pos, int _taken);
void place_on_map(Map_t* _map, Vector2_t* pos, char _char);