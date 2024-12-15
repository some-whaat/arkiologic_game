#include "Header.h"


bool circle::is_in_circle(int in_x, int in_y, float add_rad = 0) {
    return (pow(in_x - x, 2) + pow(in_y - y, 2)) <= pow((rad + add_rad), 2);;
}

bool circle::is_in_circle(position other_pos, float add_rad = 0) {
    return (pow(other_pos.x - x, 2) + pow(other_pos.y - y, 2)) <= pow((rad + add_rad), 2);
}