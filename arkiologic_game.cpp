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
    //std::ifstream sword_file;
    //sword_file.open("sword_grathics.txt");
     
    //loot.push_back(picture(sword_file, 0, 0)); 

    //space_to_dig_scene mission = space_to_dig_scene();
    collect_snake_thing mission = collect_snake_thing();

    mission.action();
}
