#include "Header.h"


/*
void fit_to_screen() {
    x = clamp(x, -(cols / 2) + (wighth / 2), (cols / 2) - (wighth / 2));
    y = clamp(y, -(rows / 2) + (hight / 2), (rows / 2) - (hight / 2));
}*/

void picture::draw_pic(std::vector<std::string>* screen_vec, Screen& screen) {
    int i = 0;
    int y_coord = (screen.coord_to_vec_space(y, 'y') - 1);

    for (int iy = y_coord - (hight / 2); iy < y_coord + (hight / 2) && iy < (&screen)->rows; iy++) {

        int x_coord = screen.coord_to_vec_space(x, 'x');

        if (iy >= 0 && x_coord + (wighth / 2) < (&screen)->cols * 2 && x_coord - (wighth / 2) > 0) {
            (*screen_vec)[iy].replace(x_coord - (wighth / 2), wighth, image_vec[i]);
            //(*screen_vec)[rows - 6].replace(cols - 6, image.size(), image);
        }
        i++;
    }
}