#include "../GP/GeneticOperator.h"
#include "../GP/TreeGenerator.h"
#include "../GP/random.hpp"
#include "NodeFilter.h"

#ifndef MUTATE_NODE_REPLACE_H
#define MUTATE_NODE_REPLACE_H


using Random = effolkronium::random_static;

class NodeReplaceMutation :public GeneticOpretator // WMinMaxHC - with minimum and maximum height control
{
private:
	std::shared_ptr<TreeGenerator> tree_gen;
public:
	NodeReplaceMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob = 1.0);
	void apply(std::weak_ptr<Individuum> individuum) override;
private:
	struct LeafFilter : public ExpressionTree::NodeFilter
	{
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
	};
	struct UnaryFilter : public ExpressionTree::NodeFilter
	{
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
	};
	struct BinaryFilter : public ExpressionTree::NodeFilter
	{
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
	};
};
#endif // !MUTATE_NODE_REPLACE_H
