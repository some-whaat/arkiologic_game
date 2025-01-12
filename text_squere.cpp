#include "Header.h"



void text_squere::draw_text(std::vector<std::string>* screen_vec, Screen& screen) {

    draw_frame(screen_vec, screen, is_big, 4);

    int i = 0;
    int y_coord = (screen.coord_to_vec_space(y, 'y') - 1);

    for (int iy = y_coord - floor(hight / 2); iy < y_coord + ceil(hight / 2)  && iy < (&screen)->rows; iy++) {

        int x_coord = screen.coord_to_vec_space(x, 'x');

        if (iy >= 0 && x_coord + (wighth / 2) < (&screen)->cols * 2 && x_coord - (wighth / 2) > 0) {
            (*screen_vec)[iy].replace(floor(x_coord - (wighth / 2)), wighth, text_vec[i]);
        }
        i++;
    }
}