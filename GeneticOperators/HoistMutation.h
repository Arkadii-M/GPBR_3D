#pragma once
#pragma once
#ifndef HOIST_MUTATION_H
#define HOIST_MUTATION_H


#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilterDefines.h"

using Random = effolkronium::random_static;

class HoistMutation :public GeneticOpretator // Select and return random subtree
{
private:
	uint min_height;
public:
	HoistMutation(uint min_height = 1, double prob = 1.0);
	virtual void apply(std::weak_ptr<Individuum> individuum) override;
};

#endif // !HOIST_MUTATION_H
