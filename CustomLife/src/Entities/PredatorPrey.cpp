#include <iostream>
#include "PredatorPrey.h"
#include "../EntityFrame.h"

//////////
// Predator
//////////

int DEFAULT_TIME_BETWEEN_BREEDS = 512;
int DEFAULT_STARTING_ENERGY = 2048;
int REPRODUCTIVE_ENERGY =  DEFAULT_STARTING_ENERGY * 2;
float CHILDREN_ENERGY_FACTOR = 0.5;
float EATING_ENERGY_FACTOR = 1;

Predator::Predator() : PixelEntity(sf::Color::Red) {
	this->energy = 0;
	this->starting_energy = 0;
}

Predator::Predator(sf::Vector2<int> pos, sf::Color color, int starting_energy) : PixelEntity(pos, color) {
	this->starting_energy = starting_energy;
	this->energy = this->starting_energy;
	this->type_id = 2;
}

Predator::Predator(sf::Vector2<int> pos, sf::Color color) : Predator(pos, color, DEFAULT_STARTING_ENERGY) {}
Predator::Predator(sf::Vector2<int> pos) : Predator(pos, sf::Color::Red) {}

void Predator::do_step() {
	//std::cout << "Predator energy is: " << this->energy << std::endl;
	if (this->energy <= 0) { // dead
		this->die();
	}
	else {
		// move randomly if possible
		int direction = this->frame->get_random_direction();
		sf::Vector2<int> new_pos = this->pos;
		PixelEntity* thing_at_new_pos;
		Predator* p;
		switch (direction) {
		case 0:
			new_pos.y--;
			// check if there's prey at the new location,
			// eat it if so
			thing_at_new_pos = this->frame->at(new_pos);
			if (thing_at_new_pos) {
				if (thing_at_new_pos->type_id == 3) {
					this->frame->destroy(thing_at_new_pos);
					this->energy += (int)(EATING_ENERGY_FACTOR * (float)starting_energy);
					// after eating the prey, if the energy of the predator
					// is high enough, a new predator will spawn in place
					// of the prey
					if (this->energy >= REPRODUCTIVE_ENERGY && this->pixel_up_free()) {
						this->energy /= 2;
						int baby_starting_energy = (int)(CHILDREN_ENERGY_FACTOR * (float)this->starting_energy);
						p = new Predator(new_pos, this->color, baby_starting_energy);
						p->add_to_frame(this->frame);
					}
				}
			}
			else {
				this->move_up();
			}
			break;
		case 1:
			new_pos.x++;
			thing_at_new_pos = this->frame->at(new_pos);
			if (thing_at_new_pos) {
				if (thing_at_new_pos->type_id == 3) {
					this->frame->destroy(thing_at_new_pos);
					this->energy += (int)(EATING_ENERGY_FACTOR * (float)starting_energy);
					if (this->energy >= REPRODUCTIVE_ENERGY && this->pixel_right_free()) {
						this->energy /= 2;
						int baby_starting_energy = (int)(CHILDREN_ENERGY_FACTOR * (float)this->starting_energy);
						p = new Predator(new_pos, this->color, baby_starting_energy);
						p->add_to_frame(this->frame);
						this->energy = this->energy / 2;
					}
				}
			}
			else {
				this->move_right();
			}
			break;
		case 2:
			new_pos.x--;
			thing_at_new_pos = this->frame->at(new_pos);
			if (thing_at_new_pos) {
				if (thing_at_new_pos->type_id == 3) {
					this->frame->destroy(thing_at_new_pos);
					this->energy += (int)(EATING_ENERGY_FACTOR * (float)starting_energy);
					if (this->energy >= REPRODUCTIVE_ENERGY && this->pixel_left_free()) {
						this->energy /= 2;
						int baby_starting_energy = (int)(CHILDREN_ENERGY_FACTOR * (float)this->starting_energy);
						p = new Predator(new_pos, this->color, baby_starting_energy);
						p->add_to_frame(this->frame);
						this->energy = this->energy / 2;
					}
				}
			}
			else {
				this->move_left();
			}
			break;
		case 3:
			new_pos.y++;
			thing_at_new_pos = this->frame->at(new_pos);
			if (thing_at_new_pos) {
				if (thing_at_new_pos->type_id == 3) {
					this->eat(thing_at_new_pos);
					this->energy += (int)(EATING_ENERGY_FACTOR * (float)starting_energy);
					if (this->energy >= REPRODUCTIVE_ENERGY && this->pixel_down_free()) {
						this->energy /= 2;
						int baby_starting_energy = (int)(CHILDREN_ENERGY_FACTOR * (float)this->starting_energy);
						p = new Predator(new_pos, this->color, baby_starting_energy);
						p->add_to_frame(this->frame);
						this->energy = this->energy / 2;
					}
				}
			}
			else {
				this->move_down();
			}
			break;
		}
		this->energy--;
	}
}

void Predator::die() {
	this->frame->destroy(this);
}

void Predator::eat(PixelEntity* prey) {
	this->frame->destroy(prey);
}

//////////
// Prey
//////////

Prey::Prey() : PixelEntity(sf::Color::Green) {
	this->breed_time = 0;
	this->steps_until_next_breeding = 0;
}

Prey::Prey(sf::Vector2<int> pos, sf::Color color, int breed_time) : PixelEntity(pos, color) {
	this->breed_time = breed_time;
	this->steps_until_next_breeding = this->breed_time;
	this->type_id = 3;
}

Prey::Prey(sf::Vector2<int> pos) : Prey(pos, sf::Color::Green) {}
Prey::Prey(sf::Vector2<int> pos, sf::Color color) : Prey(pos, color, DEFAULT_TIME_BETWEEN_BREEDS) {}


void Prey::do_step() {
	int direction = this->frame->get_random_direction();
	if (this->steps_until_next_breeding <= 0) {
		int baby_breed_time = (int)(0.25 * DEFAULT_TIME_BETWEEN_BREEDS) + 1 * this->breed_time - (rand() % (int)(0.5 * this->breed_time));
		sf::Vector2<int> new_prey_pos = this->pos;
		Prey* p;
		bool room_for_breeding = false;
		switch (direction) {
		case 0:
			if (this->pixel_up_free()) {
				new_prey_pos.y--;
				room_for_breeding = true;
			}
			break;
		case 1:
			if (this->pixel_right_free()) {
				new_prey_pos.x++;
				room_for_breeding = true;
			}
			break;
		case 2:
			if (this->pixel_left_free()) {
				new_prey_pos.x--;
				room_for_breeding = true;
			}
			break;
		case 3:
			if (this->pixel_down_free()) {
				new_prey_pos.y++;
				room_for_breeding = true;
			}
			break;
		}
		if (room_for_breeding) {
			p = new Prey(new_prey_pos, this->color, baby_breed_time);
			p->add_to_frame(this->frame);
			this->steps_until_next_breeding = this->breed_time;
		}
	}
	else {
		// move randomly if possible
		switch (direction) {
		case 0:
			this->move_up();
			break;
		case 1:
			this->move_right();
			break;
		case 2:
			this->move_left();
			break;
		case 3:
			this->move_down();
			break;
		}
		this->steps_until_next_breeding--;
	}
}

void Prey::die() {
	this->frame->destroy(this);
}
