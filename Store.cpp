#include "Header.h"




void Store::get_products() {
	std::ifstream shovel("shovel.txt");
	std::ifstream kirk("kirk.txt");

	std::ifstream rod_tool("rod_tool.txt");
	std::ifstream worm("worm.txt");

	std::ifstream boots("boots.txt");
	std::ifstream gloves("gloves.txt");

	std::ifstream banana("banana.txt");
	std::ifstream cake("cake.txt");

	awailble_equip = { equipment(shovel, "shovel", 5, 2, 0, 0), equipment(kirk, "kirk", 6, 2, 0, 0), equipment(rod_tool, "fishing rod", 5, 3, 0, 0), equipment(boots, "a really fine boots", 7, 1, 0, 0), equipment(worm, "just a single worm", 6, 3, 0, 0), equipment(gloves, "a pair of gloves", 4, 1, 0, 0), equipment(banana, "just a banana (=1 food)", 3, 9, 0, 0), equipment(cake, "a whole cake just for you! (=2 food)", 7, 99, 0, 0) };
}

void Store::add_products() {
	get_products();

	std::vector<loot> loot_quip;

	for (int i = 0; i < grid_side * grid_side; i++) {
		int re = rand_int(0, awailble_equip.size() - 1);
		all_equip.push_back(awailble_equip[re]);
		loot_quip.push_back(awailble_equip[re]);
	}

	add_grid_els(loot_quip);

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

	for (int i = 0; i < all_equip.size(); i++) {
		_frames.emplace_back(all_equip[i].x, all_equip[i].y, (cols / grid_side) * 2 - dist_bet_frames, (rows / grid_side) - dist_bet_frames);
		_pictures.push_back(all_equip[i]);
	}

	/*for (int i = 0; i < all_equip.size(); i++) {
		_frames.emplace_back(all_equip[i].x, all_equip[i].y, (cols / grid_side) * 2 - dist_bet_frames, (rows / grid_side) - dist_bet_frames);
		_pictures.push_back(all_equip[i]);
	}*/

	add_srats();
	something_changed = true;
	render();
}

void Store::make_purches() {
	if (player->money >= all_equip[selected_el].cost) {
		player->money -= all_equip[selected_el].cost;

		if (all_equip[selected_el].for_what_mission == 9) {
			player->food++;
		}
		else if (all_equip[selected_el].for_what_mission == 99) {
			player->food += 2;
		}
		else {
			player->eqip_inventory.push_back(all_equip[selected_el]);
		}

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