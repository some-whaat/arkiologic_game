#include "Header.h"




void fishing_game::action() {
    
    while (got_fish < how_much_fish_you_need && player->food - food_spend >= 0) {
        take_the_food();

        for (int i = 0; i < fish_vec.size() - onscreen_fish_am; i++) {

            int fasing = rand_int(0, 1) == 0 ? -1 : 1;

            std::ifstream fish_f;
            if (fasing == 1) {
                fish_f.open("fish_right1.txt");
            }
            else {
                fish_f.open("fish_left1.txt");
            }

            fish_vec.emplace_back(cols, rows, (cols / 2) * fasing * (-1), rand_int(-(rows / 2) + 10, (rows / 2) - 10), fish_f, fasing, fish_speed);
        }

        position dir;

        if (GetAsyncKeyState(VK_LEFT))
        {
            dir.x += -1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            dir.x += 1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_UP))
        {
            dir.y += 1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            dir.y += -1;
            something_changed = true;
        }

        dir.normalise();

        _pictures.at(0).sum(dir.mult(rod_speed));

        for (int i = 0; i < fish_vec.size(); i++) {
            fish_vec[i].move();
            if (fish_vec[i].x < -cols / 2 - 8 || fish_vec[i].x > cols / 2 + 8) {
                fish_vec.erase(fish_vec.begin() + i);
            }
        }

        _pictures.erase(_pictures.begin() + 1, _pictures.end());
        _pictures.reserve(1 + fish_vec.size());
        _pictures.insert(_pictures.begin() + 1, fish_vec.begin(), fish_vec.end());

        /*
        for (int i = 0; i < fish_vec.size(); i++) {
            if (i + 1 >= _pictures.size()) {
                _pictures.push_back(fish_vec[i]);
            }
            else {
                _pictures[i + 1] = fish_vec[i];
            }
        }*/

        something_changed = true;
        procces_collisions();
		render();
    }
    
    outtro();
}

void fishing_game::procces_collisions() {
    for (int i = fish_vec.size() - 1; i >= 0; i--) {

        if (fish_vec[i].is_in_rec(position(_pictures[0].x, _pictures[0].y - _pictures[0].hight/2), 1.5)) {
            fish_vec.erase(fish_vec.begin() + i);
            got_fish++;

            std::string new_str = "you've got " + std::to_string(got_fish) + " fish, you need " + std::to_string(how_much_fish_you_need);
            _text[1] = text_squere((int)(ceil(-rows / 2) + ceil(new_str.size() / 2) - 8), (int)(floor(rows / 2) - 3), new_str, 0);
        }
    }
}

void fishing_game::get_possible_loot() {

    std::ifstream fish("fish.txt");
    std::ifstream boot("boot.txt");
    std::ifstream fish_skeleton("fish_skeleton.txt");

    std::vector<loot> possible_loot = { loot(fish, "a fish", 7, 0, 0), loot(boot, "a single old, wet, soggy boot", 5, 0, 0), loot(fish_skeleton, "a fish skeleton (you toled the musium that it is ancient)", 6, 0, 0) };
    //std::vector<loot> possible_loot = { loot(vase, "vase", 6, 0, 0) };

    result_loot = possible_loot[rand_int(0, possible_loot.size() - 1)];
}

void fishing_game::change_dificulty() {
    food_spending += difficulty_lewel * 0.1;
    how_much_fish_you_need += difficulty_lewel * 3;
    fish_speed += difficulty_lewel * 0.75;
    rod_speed -= difficulty_lewel * 0.75;
}