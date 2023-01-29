#pragma once
#pragma once
#ifndef TERMINAL_MUTATION_H
#define TERMINAL_MUTATION_H


#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilter.h"
#include "../GP/TreeGenerator.h"

using Random = effolkronium::random_static;

class TerminalMutation :public GeneticOpretator // Select and return random subtree
{
private:
	std::shared_ptr<TreeGenerator> tree_gen;
public:
	TerminalMutation(std::shared_ptr<TreeGenerator> tree_gen,double prob = 1.0);
	virtual void apply(std::weak_ptr<Individuum> individuum) override;

private:

	struct Filter : public ExpressionTree::NodeFilter
	{
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
	};
};

#endif // !TERMINAL_MUTATION_H
