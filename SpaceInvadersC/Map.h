#pragma once
#include "Field.h"
#include <stdio.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct Map Map_t;


struct Map {
	Field_t map[MAP_WIDTH][MAP_HEIGHT];
};

void init_map(Map_t* _map);
void print_map(Map_t* _map);