#include "Header.h"

bool is_working = true;


int main()
{
    Player the_player = Player();
    //loot.push_back(picture(sword_file, 0, 0)); 
    //std::vector<Mission> missions = { space_to_dig_scene(&the_player), collect_snake_thing(&the_player) };
    //space_to_dig_scene mission = space_to_dig_scene(&the_player);
    //collect_snake_thing mission = collect_snake_thing(&the_player);

    Menu mission = Menu(&the_player);

    //missions[rand_int(0, missions.size() - 1)].action();
    mission.action();
}
