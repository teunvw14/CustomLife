#pragma once
#include "PredatorPrey.h"

class SmartPredator : public Predator {
	using Predator::Predator;
public:
	void do_step();
	void update_neighbours();
};

class SmartPrey : public Prey {
	using Prey::Prey;
public:
	void do_step();
	void breed_smart();
	int get_baby_breed_time();
};