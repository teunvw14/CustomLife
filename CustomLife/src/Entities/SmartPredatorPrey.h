#pragma once
#include "PredatorPrey.h"

class SmartPredator : public Predator {
	using Predator::Predator;
public:
	void do_step();
};

class SmartPrey : public Prey {
	using Prey::Prey;
public:
	void do_step();
	void breed_smart();
};