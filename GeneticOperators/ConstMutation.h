#pragma once
#ifndef CONSTANT_MUTATION_H
#define CONSTANT_MUTATION_H


#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilter.h"

using Random = effolkronium::random_static;

class ConstantMutation :public GeneticOpretator // Select and return random subtree
{
private:
	const double a;
	const double b;
	const double scale;
public:
	ConstantMutation(double a,double b, double scale,double prob = 1.0);
	virtual void apply(std::weak_ptr<Individuum> individuum) override;

private:

	struct Filter : public ExpressionTree::NodeFilter
	{
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
	};
};

#endif // !CONSTANT_MUTATION_H
