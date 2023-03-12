#include "Individuum.h"

Individuum::Individuum(std::unique_ptr<ExpressionTree> tree):
	tree(std::move(tree)),
	is_calculated(false),
	fitness(0.0)
{
}

Individuum::Individuum(const Individuum& rhs):
	fitness(rhs.fitness),
	is_calculated(rhs.is_calculated)
{
	if (rhs.tree)
		tree = std::move(std::make_unique<ExpressionTree>(*(rhs.tree.get())));
	else
		tree.release();
}

double Individuum::getFintness() const
{
	return fitness;
}

void Individuum::setFitness(double fit)
{
	fitness = fit;
}

bool Individuum::isCalculated() const
{
	return is_calculated;
}

void Individuum::setCalculated(bool calc)
{
	is_calculated = calc;
}

std::unique_ptr<ExpressionTree>& Individuum::getTree()
{
	return tree;
}

void Individuum::setTree(std::unique_ptr<ExpressionTree> tree)
{
	this->tree = std::move(tree);
}


std::unique_ptr<IndividuumData>& Individuum::getData() { return data; }
void Individuum::setData(std::unique_ptr<IndividuumData> data) { this->data = data; }

bool Individuum::cmp_weak(const std::weak_ptr<Individuum>& a, const std::weak_ptr<Individuum>& b)
{
	return a.lock()->fitness < b.lock()->fitness;
}
double Individuum::sum_weak(double lhs, const std::weak_ptr<Individuum>& rhs)
{
	return lhs + rhs.lock()->getFintness();
}

bool operator==(const std::weak_ptr<Individuum> a, const std::weak_ptr<Individuum> b)
{
	return a.lock() == b.lock();
}
