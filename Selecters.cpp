#include "Header.h"


void Selecters::add_srats() {
    _text.emplace_back((int)(floor(cols / 2) - 4), (int)(floor(rows / 2) - 4), "food: " + std::to_string((int)(player->food)), 0);
    _text.emplace_back(-(int)(floor(cols / 2) - 4), (int)(floor(rows / 2) - 4), "money: " + std::to_string((int)(player->money)), 0);
}


void Selecters::add_grid_els(int dist_bet_frames, std::vector<loot> el_vector) {

	int cell_x = cols / grid_side;
	int cell_y = rows / grid_side;

	int i = 0;
	for (int y = rows / 2 - cell_y / 2; y > -rows / 2; y -= cell_y) {

		for (int x = ceil(-cols / 2) + ceil(cell_x / 2) + 1; x < cols / 2; x += cell_x) {
			_frames.emplace_back(x, y, cell_x * 2 - dist_bet_frames, cell_y - dist_bet_frames);

			if (i < el_vector.size()) {
				loot new_equi = el_vector[rand_int(0, el_vector.size() - 1)];
				new_equi.x = x;
				new_equi.y = y;

				_pictures.push_back(new_equi);
				i++;
			}
		}
	}
}

void Selecters::action() {

	_frames[selected_el].is_big = true;

	render();
	something_changed = true;
	Sleep(333);

	while (!GetAsyncKeyState(VK_ESCAPE) && !is_quit)
	{
		while (GetAsyncKeyState(VK_ESCAPE)) {}
		selecting();
	}
}

void Selecters::selecting() {

	if (!GetAsyncKeyState(VK_SPACE))
	{
		if (GetAsyncKeyState(VK_LEFT)) {

			while (GetAsyncKeyState(VK_LEFT)) {}

			selected_el -= 1;

			if (selected_el < 0) {
				selected_el = _pictures.size() - 1;
			}

			for (int i = 0; i < _pictures.size(); i++) {
				_frames[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		if (GetAsyncKeyState(VK_RIGHT)) {

			while (GetAsyncKeyState(VK_RIGHT)) {}

			selected_el += 1;

			if (selected_el >= _pictures.size()) {
				selected_el = 0;
			}

			for (int i = 0; i < _pictures.size(); i++) {
				_frames[i].is_big = i == selected_el;
			}
			something_changed = true;
		}

		render();
	}
	else if (selected_el < _pictures.size()) {

		while (GetAsyncKeyState(VK_SPACE)) {}

		select_actions();

		for (int i = 0; i < _pictures.size(); i++) {
			_frames[i].is_big = i == selected_el;
		}
	}
}