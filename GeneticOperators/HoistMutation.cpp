#include "HoistMutation.h"

HoistMutation::HoistMutation(uint min_height, double prob):
	GeneticOpretator(prob),
	min_height(min_height)
{
}


void HoistMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();

	// If tree has only one node(root) generate new tree.
	if (tree->getHeight() == 0)
		return;

	auto nodes_list = tree->filterNodesIdexes(std::make_unique<HoistMutation::Filter>(3));

	if (nodes_list.size() == 0)// no node to select
		return;
	uint rand_node = *Random::get(nodes_list.begin(), nodes_list.end());

	auto observer = tree->getNodeObserver(rand_node);

	individuum.lock()->setTree(std::make_unique<ExpressionTree>(observer->subTreeCopy()));
}
HoistMutation::Filter::Filter(uint min_h):
	min_h(min_h)
{
}

bool HoistMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return 	NotRoot()(node) && MinHeight(min_h)(node);
}
