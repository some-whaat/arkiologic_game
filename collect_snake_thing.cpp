#include "Header.h"



void collect_snake_thing::grow_snake() {

    if (snake_circs.size() > 1) {
        snake_circs.push_back(circle(snake_circs[snake_circs.size() - 1], snake_body_rad));
    }

    else {
        snake_circs.push_back(circle(_pictures[0], snake_body_rad));
    }
    
}

void collect_snake_thing::procces_collisions() {
    for (int i = frut_circs.size() - 1; i >= 0; i--) {

        if (_pictures.at(0).is_in_rec(frut_circs[i], 0)) {
            grow_snake();
            frut_circs.erase(frut_circs.begin() + i);
        }

        /*
        if (frut_circs[i].is_in_circle(snake_circs[0], 2.5f)) {
            grow_snake();
            frut_circs.erase(frut_circs.begin() + i);
        }*/
    }

    for (int i = snake_circs.size() - 1; i >= 0; i--) {

        if (_pictures.at(1).is_in_rec(snake_circs[i], 0.5)) {
            snake_circs.erase(snake_circs.begin() + i);
        }
    }
}

void collect_snake_thing::action() {

    text_seq_render(introduction_text_);

    while (snake_circs.size() > 0 || frut_circs.size() > 0)
    {
        position dir;

        if (GetAsyncKeyState(VK_LEFT))
        {
            dir.x += -1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            dir.x += 1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_UP))
        {
            dir.y += 1;
            something_changed = true;
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            dir.y += -1;
            something_changed = true;
        }

        dir.normalise();

        _pictures.at(0).sum(dir.mult(speed));

        if (snake_circs.size() > 0) {
            snake_circs.at(0).move_to(_pictures.at(0), dist_between_body_parts);
        }

        for (int i = 1; i < snake_circs.size(); i++) {

            snake_circs.at(i).move_to(snake_circs.at(i - 1), dist_between_body_parts);
        }


        if (something_changed == true) {
            procces_collisions();

            render();
            something_changed = false;
        }
    }

    text_seq_render(end_text_);
}