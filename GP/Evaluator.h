#pragma once
#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <vector>
#include "Population.h"
class Evaluator
{
public:
	Evaluator() = default;
	virtual double evaluateOne(const std::weak_ptr<Individuum>) = 0;
	virtual void evaluatePopulation(Population& population) = 0;
};

#endif //EVALUATOR_H