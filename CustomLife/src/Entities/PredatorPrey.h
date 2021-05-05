#pragma once
#include "../PixelEntity.h"

class Predator : public PixelEntity {
	using PixelEntity::PixelEntity; 
private:
	int starting_energy;
	int energy;
public:
	Predator();
	Predator(sf::Vector2<int> pos);
	Predator(sf::Vector2<int> pos, sf::Color color);
	Predator(sf::Vector2<int> pos, sf::Color color, int starting_energy);
	void do_step();
	bool die_if_no_energy();
	void eat(PixelEntity* prey);
};

class Prey : public PixelEntity {
private:
	int breed_time;
public:
	int steps_until_next_breeding;
	Prey();
	Prey(sf::Vector2<int> pos);
	Prey(sf::Vector2<int> pos, sf::Color color);
	Prey(sf::Vector2<int> pos, sf::Color color, int breed_time);
	void do_step();
	void die();
	void breed_to_unsafe(sf::Vector2<int> pos);;
	void breed_to(sf::Vector2<int> pos);
	int get_baby_breed_time();
};