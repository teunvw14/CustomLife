#include "SmartPredatorPrey.h"
#include "../EntityFrame.h"


void SmartPredator::do_step() {

}

void SmartPrey::breed_smart() {
	sf::Vector2<int> neighbor_pos_1 = this->pos;
	neighbor_pos_1.y--;
	if (this->frame->grid_pos_safe(neighbor_pos_1)) { this->breed_to(neighbor_pos_1); };
	sf::Vector2<int> neighbor_pos_2 = this->pos;
	neighbor_pos_2.x++;
	if (this->frame->grid_pos_safe(neighbor_pos_2)) { this->breed_to(neighbor_pos_2); };
	sf::Vector2<int> neighbor_pos_3 = this->pos;
	neighbor_pos_3.y++;
	if (this->frame->grid_pos_safe(neighbor_pos_3)) { this->breed_to(neighbor_pos_3); };
	sf::Vector2<int> neighbor_pos_4 = this->pos;
	neighbor_pos_4.x--;
	if (this->frame->grid_pos_safe(neighbor_pos_4)) { this->breed_to(neighbor_pos_4); };
}

void SmartPrey::do_step() {
	if (this->steps_until_next_breeding <= 0) {
		this->breed_smart();
	}
	else {
		int direction = this->frame->get_random_direction();
		sf::Vector2<int> new_pos = this->pos;
		switch (direction) {
		case 0:
			new_pos.y--;
			break;
		case 1:
			new_pos.x++;
			break;
		case 2:
			new_pos.x--;
			break;
		case 3:
			new_pos.y++;
			break;
		}
		this->move_to(new_pos);
		this->steps_until_next_breeding--;
	}
}
