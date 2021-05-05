#include "SmartPredatorPrey.h"
#include "../EntityFrame.h"

int DEFAULT_TIME_BETWEEN_BREEDS_SMART = 256;

void SmartPredator::update_neighbours() {
	// Check all 4 directly neighbouring positions. Overriding
	// this function is a simple way to check if there are any
	// Prey surrounding the Predator, so that they can be eaten. (see `do_step` below)
	// This could've been done with a loop, but I'm not sure it
	// would've saved much space.
	this->neighbours = std::vector<PixelEntity*>();
	sf::Vector2<int> neighbor_pos_1 = this->pos;
	neighbor_pos_1.y--;
	this->neighbours.push_back(this->frame->at(neighbor_pos_1));
	sf::Vector2<int> neighbor_pos_2 = this->pos;
	neighbor_pos_2.x++;
	this->neighbours.push_back(this->frame->at(neighbor_pos_2));
	sf::Vector2<int> neighbor_pos_3 = this->pos;
	neighbor_pos_3.y++;
	this->neighbours.push_back(this->frame->at(neighbor_pos_3));
	sf::Vector2<int> neighbor_pos_4 = this->pos;
	neighbor_pos_4.x--;
	this->neighbours.push_back(this->frame->at(neighbor_pos_4));
}

void SmartPredator::do_step() {
	if (!this->die_if_no_energy()) {
		this->update_neighbours();
		// TODO: remove this loop and move the eating directly into `update_neighbours` - which should
		// then also be renamed to someting like 'eat_smart'
		for (auto neighbour : this->neighbours) {
			if (neighbour) {
				if (neighbour->type_id == 3) {
					this->eat(neighbour);
					return;
				}
			}
		}
		// if no prey was eaten, move in a random direction
		int direction = this->frame->get_random_direction();
		sf::Vector2<int> new_pos = this->pos;
		PixelEntity* thing_at_new_pos;
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
		this->energy--;
	}
}

void SmartPrey::breed_smart() {
	// Check all 4 directly neighbouring positions and breed
	// a new prey on that location. This could've been done with
	// a loop, but I'm not sure it would've saved much space.
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
