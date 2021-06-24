#pragma once
#include "Vector2.h"

#define ESCAPE 27
#define E_BTN 101
#define Q_BTN 113
#define R_BTN 114

static int keypressed = 0;

int get_button_down(int _btn);
void update_input();