#include "Header.h"


void space_to_dig_scene::generate_pieses() {
    enshure_cols_rows();

    std::vector<circle> posible_poses;

    for (int x = -cols / 2; x <= cols / 2; x += 5) {
        posible_poses.emplace_back(x, -1 * (rows / 2), 1);

        //std::cout << x << " " << -cols / 2 << '\n';
    }

    for (int i = 0; i < amount_of_pieces; i++) {

        int new_pos_ind = rand_int(0, posible_poses.size() - 1);
        int new_rad = rand_int(piece_rad - 4, piece_rad + 4);
        circle new_circ = posible_poses[new_pos_ind];
        new_circ.y += new_rad + new_circ.rad - 0.9f;
        new_circ.rad = new_rad;

        circles.push_back(new_circ);

        posible_poses.erase(posible_poses.begin() + new_pos_ind);
        posible_poses.push_back(new_circ);
    }
}

void space_to_dig_scene::action() {

    text_seq_render(introduction_text_);

    while (circles.size() > 0) {

        if (GetAsyncKeyState(VK_SPACE)) {

            for (int i = 0; i < dig_efficiency; i++) {

                if (circles.size() == 0) {
                    break;
                }

                circles.erase(circles.begin() + rand_int(0, circles.size() - 1));
                something_changed = true;
            }
        }

        render();
    }

    text_seq_render(end_text_);
}