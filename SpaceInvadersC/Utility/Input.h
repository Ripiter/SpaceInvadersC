#pragma once
#include "Vector2.h"

#define ESCAPE 27
#define E 101
#define Q 113
#define R 114

static int keypressed = 0;

int get_button_down(int _btn);
void update_input();