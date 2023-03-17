#pragma once
#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilterDefines.h"
#include "../TreeGenerator/FullGrow.h"
#ifndef MUTATE_SHRINK_H
#define MUTATE_SHRINK_H

using Random = effolkronium::random_static;

class ShrinkMutation :public GeneticOpretator // Select and return random subtree
{
private:
	std::shared_ptr<TreeGenerator> tree_gen;
public:
	ShrinkMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob = 1.0);
	void apply(std::weak_ptr<Individuum> individuum) override;
};

#endif // !MUTATE_HOIST_H
