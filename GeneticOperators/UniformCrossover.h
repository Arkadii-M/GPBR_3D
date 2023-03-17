#ifndef UNIFORM_CROSSOVER_H
#define UNIFORM_CROSSOVER_H
#include <algorithm>
#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "../GP/NodeObserver.h"
#include "NodeFilterDefines.h"


using Random = effolkronium::random_static;

class UniformCrossover :public GeneticOpretator
{
private:
	const double replace_prob;
public:
	UniformCrossover(double replace_prob = 0.5,double prob = 1.0);
	void apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second) override;
private:
	void commonCrossover(
		std::unique_ptr<NodeObserver> first_observer,
		std::unique_ptr<NodeObserver> second_observer);
};

#endif // !UNIFORM_CROSSOVER_H