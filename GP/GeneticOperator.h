#pragma once
#include <memory>
#include "Individuum.h"
#ifndef GENETIC_OPERATOR_H
#define GENETIC_OPERATOR_H

class GeneticOpretator
{
protected:
	const double apply_prob;
public:
	GeneticOpretator(double prob);

	//virtual void operator()(std::weak_ptr<Individuum> individuum);
	//virtual void operator()(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second);
	//virtual void operator()(std::vector< std::weak_ptr<Individuum>> individuums);
	virtual void apply(std::weak_ptr<Individuum> individuum);
	virtual void apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second);
	virtual void apply(std::vector< std::weak_ptr<Individuum>> individuums);

	double getApplyProbability() const;
};

#endif // GENETIC_OPERATOR_H
