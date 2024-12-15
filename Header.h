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

int rand_int(int down_bord, int up_bord);

class position {
public:
    float x;
    float y;

    position() : x(0), y(0) {}

    position(float in_x, float in_y) : x(in_x), y(in_y) {}

    position sum(position pos);

    position mins(position pos);

    position mult(float num);

    position div(float num);

    float dist(const position& other);

    float len();

    position normalise();

    position follow(const position& to_pos, float speed, float min_dist);

    position move_to(position& to_pos, float min_dist);

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

class picture : public position {
public:
    std::vector<std::string> image_vec;
    int hight;
    int wighth;

    picture(std::ifstream& sword_file, int in_x, int in_y) {
        x = in_x;
        y = in_y;

        std::string str;
        while (std::getline(sword_file, str))
        {
            image_vec.push_back(str);
        }

        hight = image_vec.size();
        wighth = image_vec[0].size();
    }

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

    //void draw_pic(std::vector<std::string>* screen_vec, Screen& screen);
};

class Screen {
private:

    std::vector<circle> circles;
    std::vector<picture> pictures;

public:
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;

    Screen() {
        enshure_cols_rows();
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
    std::vector<circle> pieses;
    //Screen& screen;

    space_to_dig_scene() {
        amount_of_pieces = rand_int(33, 55);

        generate_pieses();

        //something_changed = true;
    }

    void generate_pieses();

    void dig();
};

