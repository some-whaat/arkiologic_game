#include "Header.h"




void Inventory_sell::add_invent_items() {
	_pictures.clear();
	_circles.clear();
	_text.clear();
	_frames.clear();


	add_grid_els(dist_bet_frames, player->loot_inventory);

	add_srats();
}


void Inventory_sell::sell() {
	player->money += player->loot_inventory[selected_el].cost;
	player->musium_items.push_back(player->loot_inventory[selected_el]);
	player->loot_inventory.erase(player->loot_inventory.begin() + selected_el);

	something_changed = true;
}

void Inventory_sell::select_actions() {
	if (selected_el < player->loot_inventory.size()) {
		show_text_and_pic("this is " + player->loot_inventory[selected_el].name + ", it costs " + std::to_string(player->loot_inventory[selected_el].cost), _pictures[selected_el]);

		while (!GetAsyncKeyState(VK_SPACE)) {}
		while (GetAsyncKeyState(VK_SPACE)) {}

		if (yes_no_choice("do you whant to sell " + player->loot_inventory[selected_el].name + "to the musium?")) {
			sell();
		}

		add_invent_items();
		something_changed = true;

	}
}



void Inventory_return::add_invent_items() {
	_pictures.clear();
	_circles.clear();
	_text.clear();
	_frames.clear();

	std::vector<loot> eqip_screen;

	for (loot eqip : player->eqip_inventory) {
		eqip_screen.push_back(eqip);
	}

	add_grid_els(dist_bet_frames, eqip_screen);

	add_srats();
}


void Inventory_return::select_actions() {
	show_text_and_pic("this is " + player->eqip_inventory[selected_el].name, player->eqip_inventory[selected_el]);

	while (!GetAsyncKeyState(VK_SPACE)) {}
	while (GetAsyncKeyState(VK_SPACE)) {}

	if (yes_no_choice("do you whant to use " + player->eqip_inventory[selected_el].name + " for this mission?")) {

		to_return = player->eqip_inventory[selected_el].for_what_mission;
		if (player->eqip_inventory[selected_el].name != "your hand") {
			(player->eqip_inventory).erase((player->eqip_inventory).begin() + selected_el);
		}

		is_quit = true;
	}
	add_invent_items();
	something_changed = true;
}

int Inventory_return::get_to_return() {
	return to_return;
}
