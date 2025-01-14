#include "Header.h"




void Store::get_products() {
	std::ifstream sword("sword.txt");
	std::ifstream kirk("kirk.txt");

	awailble_equip = { equipment(sword, "sword", 5, 1, 0, 0), equipment(kirk, "kirk", 6, 2, 0, 0) };
}

void Store::add_products() {
	get_products();

	std::vector<loot> loot_quip;

	for (int i = 0; i < grid_side * grid_side; i++) {
		int re = rand_int(0, awailble_equip.size() - 1);
		all_equip.push_back(awailble_equip[re]);
		loot_quip.push_back(awailble_equip[re]);
	}

	add_grid_els(dist_bet_frames, loot_quip);

	for (int i = 0; i < grid_side * grid_side; i++) {
		all_equip[i].x = _pictures[i].x;
		all_equip[i].y = _pictures[i].y;
	}

	add_srats();
}

void Store::match_products() {
	_pictures.clear();
	_circles.clear();
	_text.clear();
	_frames.clear();

	for (equipment eqie : all_equip) {
		_frames.emplace_back(eqie.x, eqie.y, (cols / grid_side) * 2 - dist_bet_frames, (rows / grid_side) - dist_bet_frames);
		_pictures.push_back(eqie);
	}
	add_srats();
	something_changed = true;
	render();
}

void Store::make_purches() {
	if (player->money >= all_equip[selected_el].cost) {
		player->money -= all_equip[selected_el].cost;

		player->eqip_inventory.push_back(all_equip[selected_el]);
		all_equip.erase(all_equip.begin() + selected_el);
		text_seq_render({ text_squere("congrats, you bought it!", 0) });
	}
	else {
		text_seq_render({ text_squere("sorry, you don't have enoth money", 0) });
	}

	something_changed = true;
}

void Store::select_actions() {
	show_text_and_pic("this is " + all_equip[selected_el].name + ", it costs " + std::to_string(all_equip[selected_el].cost), _pictures[selected_el]);

	while (!GetAsyncKeyState(VK_SPACE)) {}
	while (GetAsyncKeyState(VK_SPACE)) {}

	if (yes_no_choice("do you whant to buy?")) {
		make_purches();
	}

	match_products();
	something_changed = true;
}