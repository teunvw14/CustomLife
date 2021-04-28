#include "RandomWalkEntity.h"
#include "../EntityFrame.h"

void RandomWalkEntity::do_step() {
	// TODO: make random numbers _actually_ random. The rand() function is horrible. 
	int direction = this->frame->get_random_direction();
	switch (direction) {
	case 0:
		PixelEntity::move_up();
		break;
	case 1:
		PixelEntity::move_right();
		break;
	case 2:
		PixelEntity::move_left();
		break;
	case 3:
		PixelEntity::move_down();
		break;
	}
}