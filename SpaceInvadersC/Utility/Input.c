#include "Input.h"
#include <conio.h>
int get_button_down(int _btn)
{
	if (keypressed == 0)
		return 0;

	if (keypressed == _btn) {
		keypressed = 0;
		return 1;
	}

	return 0;
}

void update_input()
{
	if (_kbhit()) {
		keypressed = _getch();
	}
}
