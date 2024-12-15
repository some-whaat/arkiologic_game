#include <iostream>
#include <windows.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "Header.h"


bool something_changed = true;

/*
float clamp(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}*/


int main()
{
    Screen screen = Screen();  

    space_to_dig_scene mission = space_to_dig_scene();

    std::ifstream sword_file;
    sword_file.open("sword_grathics.txt");
    
    picture pic = picture(sword_file, 0, 0);
    //pic.fit_to_screen();

    while (mission.pieses.size() != 0) {

        if (GetAsyncKeyState(VK_SPACE))
        {
            mission.dig();
        }

        mission.render();
        /*
        if (something_changed) {
            render(mission, pic, screen);

            something_changed = false;
        } */
    }
}
