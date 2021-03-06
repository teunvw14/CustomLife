#include <iostream>
#include "PredatorPrey.h"
#include "../EntityFrame.h"

//TODO: change these constants to be class methods or class constants, so that it 
// can easily be changed for subclasses
int DEFAULT_TIME_BETWEEN_BREEDS = 512;
int DEFAULT_STARTING_ENERGY = 2048;
int REPRODUCTIVE_ENERGY =  DEFAULT_STARTING_ENERGY * 2;
float CHILDREN_ENERGY_FACTOR = 0.5;
float EATING_ENERGY_FACTOR = 1;

//////////
// Predator
//////////


Predator::Predator(sf::Vector2<int> pos, sf::Color color) : PixelEntity(pos, color) {
	this->type_id = 2;
	this->energy = this->starting_energy;
}

Predator::Predator(sf::Vector2<int> pos, sf::Color color, int starting_energy) : Predator(pos, color) {
	this->starting_energy = starting_energy;
}

Predator::Predator(sf::Vector2<int> pos) : Predator(pos, sf::Color::Red) {}

void Predator::do_step() {
	if (!this->die_if_no_energy()) { // "if the Predator doesn't die"
		// move in a random direction:
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
		// check if there's prey at the new location, eat it if so
		thing_at_new_pos = this->frame->at(new_pos);
		if (thing_at_new_pos) {
			if (thing_at_new_pos->type_id == 3) {
				this->eat(thing_at_new_pos);
			}
		}
		else {
			this->move_to(new_pos);
		}
		this->energy--;
	}
}

bool Predator::die_if_no_energy() {
	if (this->energy <= 0) {
		this->frame->destroy(this);
		return true;
	}
	return false;
}

void Predator::eat(PixelEntity* prey) {
	// after eating the prey, if the energy of the predator
	// is high enough, a new predator will spawn in place
	// of the prey
	if (this->energy >= REPRODUCTIVE_ENERGY) {
		this->energy = (int)(this->energy * (1 - CHILDREN_ENERGY_FACTOR));
		int baby_starting_energy = (int)(CHILDREN_ENERGY_FACTOR * (float)this->starting_energy);
		Predator* p = new Predator(prey->pos, this->color, baby_starting_energy);
		p->add_to_frame(this->frame);
	}
	this->frame->destroy(prey);
	this->energy += (int)(EATING_ENERGY_FACTOR * (float)this->starting_energy);
}

//////////
// Prey
//////////

Prey::Prey(sf::Vector2<int> pos) : Prey(pos, sf::Color::Green) {}

Prey::Prey(sf::Vector2<int> pos, sf::Color color) : PixelEntity(pos, color) {
	this->type_id = 3;
	this->steps_until_next_breeding = this->breed_time;
}

Prey::Prey(sf::Vector2<int> pos, sf::Color color, int breed_time) : Prey(pos, color) {
	this->breed_time = breed_time;
	this->steps_until_next_breeding = this->breed_time;
}

void Prey::do_step() {
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
	if (this->steps_until_next_breeding <= 0) {
		this->breed_to(new_pos);
	}
	else {
		this->move_to(new_pos);
		this->steps_until_next_breeding--;
	}
}

void Prey::die() {
	this->frame->destroy(this);
}

void Prey::breed_to_unsafe(sf::Vector2<int> new_prey_pos) {
	Prey* p = new Prey(new_prey_pos, this->color, this->get_baby_breed_time());
	p->add_to_frame(this->frame);
	this->steps_until_next_breeding = this->breed_time;
}

void Prey::breed_to(sf::Vector2<int> new_prey_pos) {
	if (this->frame->grid_pos_safe(new_prey_pos)) {
		this->breed_to_unsafe(new_prey_pos);
	}
}

int Prey::get_baby_breed_time() {
	return (int)(0.25 * DEFAULT_TIME_BETWEEN_BREEDS) + this->breed_time - (rand() % (int)(0.5 * this->breed_time));
}
