#include "GeneticOperator.h"

GeneticOpretator::GeneticOpretator(double prob):
	apply_prob(prob)
{
}

void GeneticOpretator::apply(std::weak_ptr<Individuum> individuum)
{
	throw std::logic_error("this method is not used");
}

void GeneticOpretator::apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second)
{
	throw std::logic_error("this method is not used");
}

void GeneticOpretator::apply(std::vector<std::weak_ptr<Individuum>> individuums)
{
	throw std::logic_error("this method is not used");
}

double GeneticOpretator::getApplyProbability() const
{
	return apply_prob;
}
