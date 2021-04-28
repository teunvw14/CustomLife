#include <iostream>
#include <cmath>
#include "AvoidantEntity.h"
#include "RandomWalkEntity.h"
#include <SFML/Graphics.hpp>
#include "../EntityFrame.h"


void AvoidantEntity::do_step() {
	float total_weight = 0;
	float up_bias = 0;
	float right_bias = 0;
	float down_bias = 0;
	float left_bias = 0;

	float dist;
	float weight;
	sf::Vector2<int> other_pos;
	sf::Vector2<int> diff;
	this->update_neighbours();
	for (PixelEntity* other : this->neighbours) {
		diff = this->pos - other->pos;
		dist = sqrt((diff.x)*(diff.x) + (diff.y)*(diff.y));
		weight = 1 / (dist * dist);
		if (diff.x < 0) {
			left_bias += weight;
			total_weight += weight;
		} else if (diff.x > 0) {
			right_bias += weight;
			total_weight += weight;
		}
		if (diff.y < 0) {
			up_bias += weight;
			total_weight += weight;
		} else if (diff.y > 0) {
			down_bias += weight;
			total_weight += weight;
		}
	}

	if (!(up_bias == right_bias && right_bias == down_bias && down_bias == left_bias)) {
		if (up_bias >= right_bias && up_bias >= down_bias && up_bias >= left_bias) {
			//move up
			this->move_up();
		}
		else if (right_bias >= up_bias && right_bias >= down_bias && right_bias >= left_bias) {
			// move right
			this->move_right();
		}
		else if (down_bias >= up_bias && down_bias >= right_bias && down_bias >= left_bias) {
			this->move_down();
		}
		else if (left_bias >= up_bias && left_bias >= right_bias && left_bias >= down_bias) {
			this->move_left();
		}
	}
}