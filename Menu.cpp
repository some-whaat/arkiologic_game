#include "Header.h"


void Menu::action() {

	render();
	something_changed = true;
	
	Sleep(333);

	while (!GetAsyncKeyState(VK_SPACE))
	{
		if (GetAsyncKeyState(VK_UP)) {

			Sleep(66);

			selected_el -= 1;

			if (selected_el < 0) {
				selected_el = select_options.size() - 1;
			}

			for (int i = 0; i < select_options.size(); i++) {
				_text[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		if (GetAsyncKeyState(VK_DOWN)) {

			Sleep(66);

			selected_el += 1;

			if (selected_el >= select_options.size()) {
				selected_el = 0;
			}

			for (int i = 0; i < select_options.size(); i++) {
				_text[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		render();
	}

	while (GetAsyncKeyState(VK_SPACE)) {}

	switch (selected_el)
	{
	case 0:
		go_to_rungom_mission(player);
		break;

	case 1:
		Store(player).action();
		break;

	case 2:
		Musium(player).action();
		break;

	case 3:
		Inventory_sell(player).action();
		break;

	case 4:
		is_working = false;
		break;

	default:
		break;
	}
}

void Menu::select_actions() {}