#include <iostream>
#include <cmath>
#include "PixelEntity.h"
#include "EntityFrame.h"


PixelEntity::PixelEntity(sf::Vector2<int> pos, sf::Color color) {
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->color = color; 
	this->frame = nullptr;
	this->neighbour_radius = 4;
	this->type_id = -1;
}

PixelEntity::PixelEntity(sf::Vector2<int> pos) : PixelEntity(pos, sf::Color::Black) {}

PixelEntity::PixelEntity(sf::Color color) : PixelEntity(sf::Vector2<int>(0, 0), color) {};

void PixelEntity::add_to_frame(EntityFrame* frame) {
	this->frame = frame;
	frame->add_entity(this);
}

//bool PixelEntity::pixel_up_free() {
//	sf::Vector2<int> new_pos = this->pos;
//	new_pos.y--;
//	bool new_pos_within_bounds = new_pos.y >= 0;
//	bool new_pos_available = this->frame->at(new_pos) == nullptr;
//	return (new_pos_within_bounds && new_pos_available);
//}
//
//bool PixelEntity::pixel_right_free() {
//	sf::Vector2<int> new_pos = this->pos;
//	new_pos.x++;
//	bool new_pos_within_bounds = new_pos.x < this->frame->width;
//	bool new_pos_available = this->frame->at(new_pos) == nullptr;
//	bool result = new_pos_within_bounds && new_pos_available;
//	return result;
//}
//
//bool PixelEntity::pixel_down_free() {
//	sf::Vector2<int> new_pos = this->pos;
//	new_pos.y++;
//	bool new_pos_within_bounds = new_pos.y < this->frame->height;
//	bool new_pos_available = this->frame->at(new_pos) == nullptr;
//	return (new_pos_within_bounds && new_pos_available);
//}
//
//bool PixelEntity::pixel_left_free() {
//	sf::Vector2<int> new_pos = this->pos;
//	new_pos.x--;
//	bool new_pos_within_bounds = new_pos.x >= 0;
//	bool new_pos_available = this->frame->at(new_pos) == nullptr;
//	return (new_pos_within_bounds && new_pos_available);
//}

void PixelEntity::move_to(sf::Vector2<int> pos) {
	this->frame->move_entity(this, pos);
}

void PixelEntity::move_up() {
	sf::Vector2<int> new_grid_pos = this->pos;
	new_grid_pos.y--;
	this->frame->move_entity(this, new_grid_pos);
}

void PixelEntity::move_right() {
	sf::Vector2<int> new_grid_pos = this->pos;
	new_grid_pos.x++;
	this->frame->move_entity(this, new_grid_pos);
}

void PixelEntity::move_left() {
	sf::Vector2<int> new_grid_pos = this->pos;
	new_grid_pos.x--;
	this->frame->move_entity(this, new_grid_pos);
}

void PixelEntity::move_down() {
	sf::Vector2<int> new_grid_pos = this->pos;
	new_grid_pos.y++;
	this->frame->move_entity(this, new_grid_pos);
}


void PixelEntity::update_neighbours() {
	this->neighbours =  std::vector<PixelEntity*>();
	unsigned short rad = this->neighbour_radius;
	for (int y = this->pos.y - rad; y <= this->pos.y + rad; y++) {
		for (int x = this->pos.x - rad; x <= this->pos.x + rad; x++) {
			sf::Vector2<int> grid_position(x, y);
			PixelEntity* next_neighbour = this->frame->at(grid_position);
			if (next_neighbour) {
				this->neighbours.push_back(next_neighbour);
			}
		}
	}
}


