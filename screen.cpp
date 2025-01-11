#include "Header.h"



void Screen::enshure_cols_rows() {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    cols = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

int Screen::coord_to_vec_space(int coord, char coord_name) {
    //this->enshure_cols_rows();

    switch (coord_name)
    {
    case 'x':
        return (coord + (cols / 2)) * 2;
        break;

    case 'y':
        return (rows / 2) - coord;
        break;

    default:
        break;
    }
}


char Screen::pix_calc(int x, int y) {
    for (std::vector<circle>*& circs_vec : _circles) {
        for (circle circ : *circs_vec) {
            if (circ.is_in_circle(x, y, 0)) {

                float dist = circ.dist(position(x, y));

                return rend_style[(int)((dist / circ.rad) * 10)];
            }
        }
    }
/*
    for (circle circ : *_circles[0]) {
        if (circ.is_in_circle(x, y, 0)) {

            float dist = circ.dist(position(x, y));

            return rend_style[(int)((dist / circ.rad) * 10)];
            //return std::string(2, ".....::#@@"[(int)((dist / piece.rad) * 10)]);
            //"@@00%**+:."
            //"@&%#0*+=-:"
            //".....::#@@"
        }
    }*/

    return ' ';
}

void Screen::render() {

    if (something_changed) {
        system("cls");

        enshure_cols_rows();

        screen_vec = {};


        for (int i = 0; i < rows; i++) {
            screen_vec.emplace_back(cols * 2, ' ');
        }

        for (picture pic : _pictures) {
            pic.draw_pic(&screen_vec, *this);
        }
        
        for (int y = rows / 2; y > -1 * (rows / 2); y--) {

            //std::string row_str = "";

            for (int x = -1 * (cols / 2); x < cols / 2; x++) {

                char pix = pix_calc(x, y);

                if (pix != ' ') {
                    screen_vec[(rows / 2) - y].replace((x + (cols / 2)) * 2, 2, std::string(2, pix));
                    //screen_vec[(rows / 2) - y].replace((x + (cols / 2)), 2, std::string(1, pix));

                }
            }

            if (y != -1 * (rows / 2) + 1) {
                //row_str += "\n";
                screen_vec[(rows / 2) - y] += '\n';
            }
        }
        //pictures[0].draw_pic(&screen_vec, *this);

        for (std::string str : screen_vec) {
            std::cout << str;
        }

        Sleep(MBF);
    }
    something_changed = false;
}
