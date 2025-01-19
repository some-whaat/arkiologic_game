#include "Header.h"

bool is_working = true;


int main()
{
    //SetConsoleOutputCP(CP_UTF8);
    Screen screen;
    std::ifstream heading("name_text.txt");

    screen.text_seq_render({text_squere("welcme to my game!!! (hit space to skip the dialogue)", 0)});
    screen.show_text_and_pic("it is called", picture(heading, 0, 0));
    screen.text_seq_render({ 
        text_squere("(..soo it is not really called anything)", 0),
        text_squere("anyway, you're an archaeologist who goes on archaeological expeditions hoping to put together a personal exhibition at a local museum and not starve to death on the way", 55), 
        text_squere("your goal is to collect all 9 relics in the museum, but be careful! you will lose if you run out of food", 55), 
        text_squere("you can buy and use different tools for missions. if you choose the right tool, the mission will become easier, but if you choose the wrong one, the mission will become more difficult. also you always have your hand! it doesn't change the difficulty at all", 55),
        text_squere("use arrow keys, spacebar and escape button to navigate in the menus", 0),
        text_squere("good luck!", 0), });

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
