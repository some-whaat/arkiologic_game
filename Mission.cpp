#include "Header.h"



void Mission::take_the_food() {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    food_spend = food_spending * (std::chrono::duration_cast<std::chrono::seconds>(now - begin_time).count());

    std::string new_num = std::to_string((int)(player->food - food_spend));
    _text[0] = text_squere((int)(floor(rows / 2) - ceil(new_num.size() / 2)), (int)(floor(rows / 2) - 3), "food left: " + new_num, 0);
}

void Mission::outtro() {

    if (player->food - food_spend < 0) {
        sorry_you_died();
    }
    else {
        text_seq_render(end_text_);

        player->food -= food_spend;
        player->loot_inventory.push_back(result_loot);

        _pictures.clear();
        _circles.clear();
        _text.clear();
        _frames.clear();

        //_text.emplace_back(0, rows / 2 - 4, "congrats, you've found a " + result_loot.name, 0);
        //_pictures.push_back(result_loot);

        show_text_and_pic("you've found " + result_loot.name + ", it costs " + std::to_string(result_loot.cost), result_loot);

        show_vert_text({ "you've spend " + std::to_string((int)food_spend) + " food", "now you have: " + std::to_string((int)(player->food)) }, 5, 0);
    }
}

void Mission::intro() {

    text_seq_render(introduction_text_);

    int chosen_mission_type;
    Inventory_return invent = Inventory_return(player);
    invent.action();
    chosen_mission_type = invent.get_to_return();

    if (chosen_mission_type == this_mission_type) {

        difficulty_lewel = -1;
        text_seq_render({ text_squere("you've selected the right instrument!!", 0) });
    }
    else if (chosen_mission_type == -1) {

        difficulty_lewel = 0;
        text_seq_render({ text_squere("trusty hand will never let you down", 0) });
    }
    else {

        difficulty_lewel = 1;
        text_seq_render({ text_squere("pu pu, this one does not suit here", 0) });
    }

    text_seq_render(aftertroduction_text_);

    change_dificulty();
    get_possible_loot();
}

void Mission::sorry_you_died() {
    text_seq_render({ text_squere("you have no food left, soo.. unforchunatly, you have died of hunger :(((", 44), text_squere("sorry :/", 0) });
    is_working = false;
}