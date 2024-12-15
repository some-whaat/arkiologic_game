#include "Header.h"



int rand_int(int down_bord, int up_bord) {

    return std::rand() % up_bord + down_bord;
}
