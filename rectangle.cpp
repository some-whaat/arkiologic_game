#include "Header.h"



bool rectangle::is_in_rec(position other_pos, float add_dist) {
	return other_pos.x < x + (wighth / 2) + add_dist && other_pos.x > x - (wighth / 2) - add_dist && other_pos.y < y + (hight / 2) + add_dist && other_pos.y > y - (hight / 2) - add_dist;
}

bool rectangle::is_in_rec(int in_x, int in_y, float add_dist) {
	return in_x < x + (wighth / 2) + add_dist && in_x > x - (wighth / 2) - add_dist && in_y < y + (hight / 2) + add_dist && in_y > y - (hight / 2) - add_dist;
}