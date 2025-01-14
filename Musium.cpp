#include "Header.h"
  

void Musium::add_items() {
	_pictures.clear();
	_circles.clear();
	_text.clear();
	_frames.clear();

	add_grid_els(dist_bet_frames, player->musium_items);
}

void Musium::select_actions() {
	if (selected_el < player->musium_items.size()) {
		show_text_and_pic("this is " + player->musium_items[selected_el].name, player->musium_items[selected_el]);

		while (!GetAsyncKeyState(VK_SPACE)) {}

		add_items();
	}
	
}
