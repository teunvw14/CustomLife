#include <algorithm>
#include <iostream>
#include "PixelEntity.h"
#include "Entities/RandomWalkEntity.h"
#include "EntityFrame.h"
#include "util/directions.h"


EntityFrame::EntityFrame(size_t w, size_t h) {
	this->width = w;
	this->height = h;
	this->is_full = false;
	this->available_pixels = this->width * this->height;
	this->setup_pixel_array();
	this->entity_grid = std::vector<PixelEntity *>(width * height, nullptr);
	this->random_direction_generator = std::mt19937(this->rand_dev());
	this->unif_distr = std::uniform_int_distribution<int>(0, 3);
	this->toroid_grid = false;
}

EntityFrame::EntityFrame() : EntityFrame(0, 0) {}

EntityFrame::~EntityFrame() {
	delete[] this->pixel_array;
}

void EntityFrame::setup_pixel_array(sf::Color background_color) {

	this->pixel_array = new sf::Uint8[this->width * this->height * 4];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < this->width; x++) {
			size_t index = this->width * y + x;
			pixel_array[4 * (index)+0] = background_color.r;
			pixel_array[4 * (index)+1] = background_color.g;
			pixel_array[4 * (index)+2] = background_color.b;
			pixel_array[4 * (index)+3] = background_color.a;
		}
	}

}

void EntityFrame::do_step() {
	for (int i = 0; i < this->entities.size(); i++) {
		//std::cout << "Doin step for entity no. " << i << std::endl;
		this->entities[i]->do_step();
	}
}


bool EntityFrame::add_entity(PixelEntity* ent) {
	if (this->is_full) {
		return false;
	}
	else {
		this->entities.push_back(ent);
		int position_in_grid = ent->pos.y* width + ent->pos.x;
		this->entity_grid[position_in_grid] = ent;
		this->set_pixel(position_in_grid, ent->color);

		this->available_pixels--;
		if (this->available_pixels <= 0) {
			this->is_full = true;
		}
		return true;
	}
}

void EntityFrame::destroy(PixelEntity* ent) {
	//std::cout << "Destroying pixel at " << ent << std::endl;
	this->entity_grid[ent->pos.y * this->width + ent->pos.x] = nullptr;
	this->set_pixel(ent->pos, sf::Color::Black);
	auto index = std::find(this->entities.begin(), this->entities.end(), ent);
	this->entities.erase(index);
	delete ent;
	this->available_pixels++;
}

void EntityFrame::set_pixel(int position_in_grid, sf::Color color) {
	int offset = 4 * position_in_grid;
	this->pixel_array[offset + 0] = color.r;
	this->pixel_array[offset + 1] = color.g;
	this->pixel_array[offset + 2] = color.b;
	this->pixel_array[offset + 3] = color.a;
}

void EntityFrame::set_pixel(sf::Vector2<int> vec_pos, sf::Color color) {
	int position_in_grid = vec_pos.y * width + vec_pos.x;
	this->set_pixel(position_in_grid, color);

}

PixelEntity* EntityFrame::at(sf::Vector2<int> pos) {
	if (this->toroid_grid) {
		sf::Vector2<int> adjusted_to = pos;
		adjusted_to.x = adjusted_to.x % this->width;
		adjusted_to.y = adjusted_to.y % this->height;
		return at_unsafe(adjusted_to);
	}
	else if (pos.x < this->width && pos.x >= 0 && pos.y < this->height && pos.y >= 0) {
		return this->entity_grid[pos.y * this->width + pos.x];
	}
	return nullptr;
}

PixelEntity* EntityFrame::at_unsafe(sf::Vector2<int> pos) {
	// check for an entity (without checking if the possition is legal)
	// use at your own discretion
	return this->entity_grid[pos.y * this->width + pos.x];
}

int EntityFrame::get_random_direction() {
	return this->unif_distr(this->random_direction_generator);
}

bool EntityFrame::grid_pos_available(sf::Vector2<int> pos) {
	if (bool new_pos_within_bounds = pos.x >= 0 && pos.y >= 0 && pos.x < this->width && pos.y < this->height) {
		if (bool new_pos_available = this->at_unsafe(pos) == nullptr) {
			return true;
		}
	}
	return false;
}

void EntityFrame::move_entity(PixelEntity* pixel_to_move, sf::Vector2<int> to) {
	sf::Vector2<int> adjusted_to = to;
	if (this->toroid_grid) {
		adjusted_to.x = adjusted_to.x % this->width;
		adjusted_to.y = adjusted_to.y % this->height;
	}
	// check direction possible:
	if (bool new_pos_available = this->at_unsafe(adjusted_to) == nullptr) {
		sf::Vector2<int> from = pixel_to_move->pos;
		this->set_pixel(from, sf::Color::Black);
		this->entity_grid[from.y * this->width + from.x] = nullptr;
		this->entity_grid[adjusted_to.y * this->width + adjusted_to.x] = pixel_to_move;
		pixel_to_move->pos = adjusted_to;
		this->set_pixel(adjusted_to, pixel_to_move->color);
	}
}

