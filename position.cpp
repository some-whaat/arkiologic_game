#include "Header.h"

void position::sum(position pos) {

    x += pos.x;
    y += pos.y;
}

position position::mins(position pos) {
    position n_pos;

    n_pos.x = x - pos.x;
    n_pos.y = y - pos.y;

    return n_pos;
}

position position::mult(float num) {
    return position(x * num, y * num);
}

position position::div(float num) {
    return position(x / num, y / num);
}

float position::dist(const position& other) {
    return std::sqrt(pow((other.x - x), 2) + pow((other.y - y), 2));
}

float position::len() {
    return std::sqrt(pow(x, 2) + pow(y, 2));
}

position position::normalise() {
    float len = this->len();
    if (len == 0) return *this;
    return this->div(len);
}

void position::follow(const position& to_pos, float speed, float min_dist = 0) {

    if (!(position(x, y).dist(to_pos) <= min_dist)) {

        position between_vec = position(to_pos.x - x, to_pos.y - y);
        between_vec = between_vec.normalise();
        between_vec = between_vec.mult(speed);

        this->sum(between_vec);
        //return position(x, y).sum(between_vec);
    }

}

void position::move_to(position& to_pos, float min_dist = 0) {
    position between_vec = to_pos.mins(*this);
    float len = between_vec.len();

    if (len > min_dist) {
        this->sum(between_vec.mult((len - min_dist) / len));
        //return position(x, y).sum(between_vec.mult((len - min_dist) / len));
    }
    //return *this;
}

position position::coords_to_vec_space(position coord_pos, int cols, int rows) {
    return position(coord_pos.x + cols / 2, ((rows / 2) - coord_pos.y) * 2);
}