#include "RandomAvoidantEntity.h"
#include "../EntityFrame.h"

void RandomAvoidantEntity::do_step() {
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
		dist = sqrt((diff.x) * (diff.x) + (diff.y) * (diff.y));
		weight = 1 / (dist * dist);
		if (diff.x < 0) {
			left_bias += weight;
			total_weight += weight;
		}
		else if (diff.x > 0) {
			right_bias += weight;
			total_weight += weight;
		}
		if (diff.y < 0) {
			up_bias += weight;
			total_weight += weight;
		}
		else if (diff.y > 0) {
			down_bias += weight;
			total_weight += weight;
		}
	}

	// TODO: make random numbers _actually_ random. The rand() function is horrible. 
	int direction = this->frame->get_random_direction();

	if (!(up_bias == right_bias && right_bias == down_bias && down_bias == left_bias)) {
		if (float(direction) <= (3 * up_bias / total_weight)) {
			this->move_up();
		}
		else if (float(direction) <= (3 * (up_bias + right_bias) / total_weight)) {
			this->move_right();
		}
		else if (float(direction) <= (3 * (up_bias + right_bias + down_bias) / total_weight)) {
			this->move_down();
		}
		else if (float(direction) <= (3 * (up_bias + right_bias + down_bias + left_bias) / total_weight)) {
			this->move_left();
		}
	}

}