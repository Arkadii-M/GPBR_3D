#pragma once
#ifndef GP_H
#define GP_H
#include <memory>
#include "Evaluator.h"
#include "TreeGenerator.h"

class GP// Basic class for implement different genetic models (r-model,dynamic model,etc.)
{
protected:
	std::unique_ptr<Evaluator> eval;
	std::shared_ptr<TreeGenerator> generator;
	Population population;
	uint max_no_change_iter;
	double delta_max;
public:
	GP(std::unique_ptr<Evaluator> ev,
		std::shared_ptr<TreeGenerator> gen,
		uint max_n_change,double delta);

	virtual bool execute(uint iter) = 0;
	virtual void generatePopulation(uint pop_size) = 0;

	void setMaxNoChangeIter(uint no_change);
	void setFindError(double err);

	std::weak_ptr<Individuum> GetBest();
	Population& GetPopulation();
};

#endif //GP_H