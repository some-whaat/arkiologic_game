#include "Header.h"



void Mission::take_the_food() {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

    food_spend = food_spending * (std::chrono::duration_cast<std::chrono::seconds>(now - begin_time).count());

    std::string new_num = std::to_string((int)(player->food - food_spend));
    _text[0] = text_squere((int)(floor(rows / 2) - 2), (int)(floor(rows / 2) - ceil(new_num.size() / 2) - 3), "food left: " + new_num, 0);
}