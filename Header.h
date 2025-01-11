#pragma once

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
#include <cctype>
#include <random>
#include <climits>
#include <cstdlib>

class Screen;

int rand_int(int down_bord, int up_bord);

class position {
public:
    float x;
    float y;

    position() : x(0), y(0) {}

    position(float in_x, float in_y) : x(in_x), y(in_y) {}

    void sum(position pos);

    position mins(position pos);

    position mult(float num);

    position div(float num);

    float dist(const position& other);

    float len();

    position normalise();

    void follow(const position& to_pos, float speed, float min_dist);

    void move_to(position& to_pos, float min_dist);

    position coords_to_vec_space(position coord_pos, int cols, int rows);
};

class circle : public position {
public:
    float rad;        

    circle() : rad(1) {
        x = 0;
        y = 0;
    }

    circle(float in_x, float in_y, float radius) : rad(radius) {
        x = in_x;
        y = in_y;
    }

    circle(position in_pos, float radius) : rad(radius) {
        x = in_pos.x;
        y = in_pos.y;
    }

    bool is_in_circle(int in_x, int in_y, float add_rad);

    bool is_in_circle(position other_pos, float add_rad);
};

class rectangle : public position {
public:
    float hight;
    float wighth;

    rectangle() {}

    rectangle(float in_x, float in_y, float in_hight, float in_wighth) : hight(in_hight), wighth(in_wighth) {
        x = in_x;
        y = in_y;
    }

    bool is_in_rec(position other_pos, float add_dist);

    bool is_in_rec(int in_x, int in_y, float add_dist);
};

class picture : public rectangle {
public:
    std::vector<std::string> image_vec;

    picture(std::ifstream& file, int in_x, int in_y) {
        x = in_x;
        y = in_y;

        std::string str;
        while (std::getline(file, str))
        {
            image_vec.push_back(str);
        }

        hight = image_vec.size();
        wighth = image_vec[0].size();
    }

    /*picture(std::vector<std::string> file_name, int in_x, int in_y) {
        x = in_x;
        y = in_y;

        //std::ifstream in(file_name);

        std::ifstream file;
        file.open(file_name, std::ios_base::in);

        hight = image_vec.size();
        wighth = image_vec[0].size();
    }*/

    picture(std::vector<std::string> in_image_vec, int in_x, int in_y) : image_vec(in_image_vec) {
        x = in_x;
        y = in_y;

        hight = image_vec.size();
        wighth = image_vec[0].size();
    }

    /*
    void fit_to_screen() {
        x = clamp(x, -(cols / 2) + (wighth / 2), (cols / 2) - (wighth / 2));
        y = clamp(y, -(rows / 2) + (hight / 2), (rows / 2) - (hight / 2));
    }*/

    void draw_pic(std::vector<std::string>* screen_vec, Screen& screen);
};

class Loot : picture {

};

//void download_loot();

class Screen {
private:
    std::vector<std::string> screen_vec;

protected:
    bool something_changed = true;
    const int MBF = 77; //milliseconds between frames
    std::string rend_style = "0000000000";

public:

    std::vector<std::vector<circle>*> _circles;
    std::vector<picture> _pictures;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;

    Screen() {
        enshure_cols_rows();
        /*
        for (int i = 0; i < cols; i++) {
            screen_vec.push_back(std::string(rows, ' '));
        }
        */
    }

    void enshure_cols_rows();

    int coord_to_vec_space(int coord, char coord_name);

    char pix_calc(int x, int y);

    //void draw_pic(std::vector<std::string>* screen_vec, Screen& screen);

    void render();

};

class Scene {
public:
    Screen screen;

    Scene() : screen(Screen()) {}
};

class space_to_dig_scene : public Screen {
public:
    int amount_of_pieces;
    std::vector<circle> circles;
    //Screen& screen;

    float piece_rad = 4;
    int dig_efficiency = 3;

    space_to_dig_scene() {
        _circles.push_back(&circles);

        amount_of_pieces = 88;

        generate_pieses();
        
        std::ifstream sword_file;
        sword_file.open("sword.txt");

        _pictures.push_back(picture(sword_file, 0, 0));

        //pictures.push_back(loot[rand_int(0, loot.size() - 1)]);

        rend_style = ".....::==@";
        //"@@00%**+:."
        //"@&%#0*+=-:"
        //".....::#@@"
    }

    void generate_pieses();

    void action();
};

class collect_snake_thing : public Screen {
public:
    const float speed = 2;
    
    const float snake_body_rad = 1.7f;
    const float food_rad = 1.1f;
    const float dist_between_body_parts = 5;
    const int start_food_am = 22;

    std::vector<circle> snake_circs;
    std::vector<circle> frut_circs;


    collect_snake_thing() {

        for (int i = 0; i < 0; i++) {
            grow_snake();
        }

        enshure_cols_rows();

        for (int i = 0; i < start_food_am; i++) {
            frut_circs.push_back(circle(rand_int(-1 * (cols / 2), (cols / 2)), rand_int(-1 * (rows / 2), (rows / 2)), food_rad));
        }

        _circles.push_back(&snake_circs);
        _circles.push_back(&frut_circs);

        std::ifstream chest_file;
        chest_file.open("chest.txt");

        std::ifstream dude;
        dude.open("dude.txt");

        _pictures.push_back(picture(dude, 0, 0));

        _pictures.push_back(picture(chest_file, rand_int(-1 * (cols / 2) + 7, (cols / 2) - 7), rand_int(-1 * (rows / 2) + 7, (rows / 2) - 7)));

        rend_style = "...:;+==#@";
    }

    void action();

    void procces_collisions();

    void grow_snake();
};

/*
class Game {
public:

    Game() {
        download_loot();

        Screen screen = Screen();

        space_to_dig_scene mission = space_to_dig_scene();

        while (mission.circles.size() != 0) {

            if (GetAsyncKeyState(VK_SPACE))
            {
                mission.dig();
            }

            mission.render();
        }
    }
};*/