#pragma once
#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilterDefines.h"
#ifndef MUTATE_SWAP_H
#define MUTATE_SWAP_H



using Random = effolkronium::random_static;

class SwapMutation :public GeneticOpretator // Select and return random subtree
{
public:
	SwapMutation(double prob = 1.0);
	void apply(std::weak_ptr<Individuum> individuum) override;
};

#endif // !MUTATE_SWAP_H
