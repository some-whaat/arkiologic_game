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

class position;
class circle;
class rectangle;
class text_squere;
class picture;
class loot;
class Screen;
class Scene;

//extern enum menu_options;

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

    void draw_circ(std::vector<std::string>* screen_vec, Screen& screen, std::string rend_style);
};

class rectangle : public position {
public:
    float hight;
    float wighth;

    rectangle() {
        x, y, hight, wighth = 0;
    }

    rectangle(float in_x, float in_y, float in_hight, float in_wighth) : hight(in_hight), wighth(in_wighth) {
        x = in_x;
        y = in_y;
    }

    bool is_in_rec(position other_pos, float add_dist);

    bool is_in_rec(int in_x, int in_y, float add_dist);

    void draw_rec(std::vector<std::string>* screen_vec, Screen& screen, char fill, int add_val);

    void draw_frame(std::vector<std::string>* screen_vec, Screen& screen, bool is_big, int add_val);
};

class text_squere : public rectangle {
public:
    std::vector<std::string> text_vec;

    bool is_big = false;

    text_squere() : text_vec({}) {}

    text_squere(std::string in_text, int in_wighth) {
        x, y = 0;

        if (in_wighth == 0) {
            wighth = in_text.size();
            text_vec.push_back(in_text);
            hight = 1;
        }
        else {
            wighth = in_wighth;

            //std::string add_line = std::string(' ', in_text.size() % (int)wighth);
            //in_text += add_line;

            for (int i = 0; i < std::ceil(in_text.size() / wighth) * wighth; i += wighth) {
                std::string new_line = in_text.substr(i, wighth);

                if (new_line.size() < wighth) {
                    int coun = wighth - new_line.size();
                    for (int i = 0; i < coun; i++) {
                        new_line += ' ';
                    }
                }


                text_vec.push_back(new_line);
            }

            hight = text_vec.size();
        }
    }

    text_squere(int in_x, int in_y, std::string in_text, float in_wighth) {
        x = in_x;
        y = in_y;

        if (in_wighth == 0) {
            wighth = in_text.size();
            text_vec.push_back(in_text);
            hight = 1;
        }
        else {
            wighth = in_wighth;

            //std::string add_line = std::string(' ', in_text.size() % (int)wighth);
            //in_text += add_line;

            for (int i = 0; i < std::ceil(in_text.size() / wighth) * wighth; i += wighth) {
                std::string new_line = in_text.substr(i, wighth);

                if (new_line.size() < wighth) {
                    int coun = wighth - new_line.size();
                    for (int i = 0; i < coun; i++) {
                        new_line += ' ';
                    }
                }


                text_vec.push_back(new_line);
            }

            hight = text_vec.size();
        }
    }

    void draw_text(std::vector<std::string>* screen_vec, Screen& screen);
};

class picture : public rectangle {
public:
    std::vector<std::string> image_vec;

    picture() : image_vec({}) {}

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

class loot : public picture {
public:
    std::string name;

    loot() : name("") {}

    loot(std::ifstream& file, std::string in_name, int in_x, int in_y) : name(in_name) {
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
};

//void download_loot();

class Screen {

protected:
    std::vector<std::string> screen_vec;

    bool something_changed = true;
    const int MBF = 77; //milliseconds between frames


public:

    std::string rend_style = "0000000000";

    std::vector<std::vector<circle>*> _circles;
    std::vector<picture> _pictures;
    std::vector<text_squere> _text;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;

    Screen() {

        _circles, _pictures, _text = {};

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

    void text_seq_render(std::vector<text_squere> text_seq);

};

class Player {
public:
    unsigned int money = 0;
    float food = 0;

    std::vector<loot> inventory = {};

    Player() {}

};

class Mission : public Screen {
public:
    std::vector<text_squere> introduction_text_;
    std::vector<text_squere> end_text_;
    loot result_loot;

    text_squere food_text;
    float food_spending = 0.25f;
    float food_spend = 0;

    Player* player;

    std::chrono::steady_clock::time_point begin_time;

    //difficulty_lewel

    Mission() {
        food_text = text_squere("", 0);
        _text.push_back(food_text);
    }

    //virtual void action() = 0;
    //virtual void get_possible_loot() = 0;

    void take_the_food();

};

class space_to_dig_scene : public Mission {
public:
    int amount_of_pieces;
    std::vector<circle> circles;
    //Screen& screen;

    float piece_rad = 4;
    int dig_efficiency = 3;

    space_to_dig_scene(Player* in_player) {

        food_spending += 0.3f;

        begin_time = std::chrono::steady_clock::now();

        player = in_player;

        introduction_text_ = { text_squere("destroy those rock ruins, maybe there are something cool behind them!", 0), text_squere("hit space key to dig", 0) };
        end_text_ = { text_squere("congrats!", 0) };

        _circles.push_back(&circles);

        amount_of_pieces = 111;

        generate_pieses();
        
        get_possible_loot();
        _pictures.push_back(result_loot);

        //pictures.push_back(loot[rand_int(0, loot.size() - 1)]);

        rend_style = "  ...::!=@";
        //"@@00%**+:."
        //"@&%#0*+=-:"
        //".....::#@@"
    }

    void generate_pieses();

    void action();

    void get_possible_loot();
};

class collect_snake_thing : public Mission {
public:
    const float speed = 2;
    
    const float snake_body_rad = 1.7f;
    const float food_rad = 1.1f;
    const float dist_between_body_parts = 5;
    const int start_food_am = 22;

    std::vector<circle> snake_circs;
    std::vector<circle> frut_circs;


    collect_snake_thing(Player* in_player) {

        begin_time = std::chrono::steady_clock::now();
        get_possible_loot();
        player = in_player;

        introduction_text_ = { text_squere("put all the rocks into the chest. they are.. obviously VERY important rocks!!", 0), text_squere("use arrow keys to navigate", 0) };
        end_text_ = { text_squere("congrats!", 0) };

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

    void get_possible_loot();

    void procces_collisions();

    void grow_snake();
};

void go_to_rungom_mission(Player* the_player);

class Menu : public Screen {
private:
    std::vector<std::string> select_options = { "go to a mission", "go to the shop", "go to the musium" };
    Player* player;
    //std::vector<text_squere> select_texts;
    int selected_el = 0;

public:
    Menu(Player* in_player) : player(in_player){
        int step = 5;
        int i = 0;

        for (int y = (((int)select_options.size() - 1) / 2) * step; y >= -(((int)select_options.size() - 1) / 2) * step && i < select_options.size(); y -= step) {
            _text.emplace_back(0, y, select_options[i], 20);

            i++;
        }

        for (int i = 0; i < _text.size(); i++) {
            _text[i].is_big = i == selected_el;
        }
    }

    void action();
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