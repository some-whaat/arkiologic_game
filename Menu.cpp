#include "Header.h"


void Menu::action() {
	
	while (!GetAsyncKeyState(VK_SPACE))
	{

		if (GetAsyncKeyState(VK_UP))
		{
			selected_el -= 1;

			if (selected_el < 0) {
				selected_el = _text.size() - 1;
			}

			for (int i = 0; i < _text.size(); i++) {
				_text[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			selected_el += 1;

			if (selected_el >= _text.size()) {
				selected_el = 0;
			}

			for (int i = 0; i < _text.size(); i++) {
				_text[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		render();
	}
	go_to_rungom_mission(player);
}