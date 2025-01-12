#include "Header.h"


bool circle::is_in_circle(int in_x, int in_y, float add_rad = 0) {
    return (pow(in_x - x, 2) + pow(in_y - y, 2)) <= pow((rad + add_rad), 2);;
}

bool circle::is_in_circle(position other_pos, float add_rad = 0) {
    return (pow(other_pos.x - x, 2) + pow(other_pos.y - y, 2)) <= pow((rad + add_rad), 2);
}

void circle::draw_circ(std::vector<std::string>* screen_vec, Screen& screen, std::string rend_style) {

    int side = rad * 2 + 1;

    int y_coord = (screen.coord_to_vec_space(y, 'y') - 1);

    int x_start = x - floor(side / 2);
    int x_end = x + ceil(side / 2);
    int y_start = y - floor(side / 2);

    for (int iy = y_coord - floor(side / 2); iy < y_coord + ceil(side / 2) && iy < (&screen)->rows; iy++) {

        int x_coord = screen.coord_to_vec_space(x, 'x');
        std::string line = "";

        for (int ix = x_start; ix < x_end; ix += 1) {
            if (this->is_in_circle(ix, y_start, 0)) {

                float dist = this->dist(position(ix, y_start));

                std::string pix = std::string(2, rend_style[(int)((dist / rad) * 10)]);
                line += pix;// rend_style[(int)((dist / rad) * 10)];
            }
            else {
                line += '  ';
            }
        }

        if (iy >= 0 && (x_coord + side) < (&screen)->cols * 2 && x_coord - side > 0) {
            (*screen_vec)[iy].replace(x_coord - side, side *2, line);
            //(*screen_vec)[rows - 6].replace(cols - 6, image.size(), image);
        }

        y_start++;
    }
}