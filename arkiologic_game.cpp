#include "Header.h"

bool is_working = true;


int main()
{

    Player the_player = Player(22, 22);
    //loot.push_back(picture(sword_file, 0, 0)); 
    //std::vector<Mission> missions = { space_to_dig_scene(&the_player), collect_snake_thing(&the_player) };
    //space_to_dig_scene mission = space_to_dig_scene(&the_player);
    //collect_snake_thing mission = collect_snake_thing(&the_player);

    //Inventory mission = Inventory(&the_player);
    Menu mission = Menu(&the_player);
    //Store mission = Store(&the_player);
    //Musium mission = Musium(&the_player);

    //missions[rand_int(0, missions.size() - 1)].action();
    while (is_working) {
        Menu(&the_player).action();
    }
}
