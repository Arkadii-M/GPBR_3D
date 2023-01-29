#include "SwapMutation.h"

SwapMutation::SwapMutation(double prob):
	GeneticOpretator(prob)
{
}

void SwapMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();
	if (tree->getHeight() == 0)
		return;

	auto nodes_list = tree->filterNodesIdexes(std::make_unique<SwapMutation::Filter>());
	if (nodes_list.size() == 0)
		return;

	uint rand_node = *Random::get(nodes_list.begin(), nodes_list.end());
	auto observer = tree->getNodeObserver(rand_node);
	auto left = observer->getLeft();
	auto right = observer->getRight();
	ExpressionTree::NodeObserve::SwapSubTrees(left, right);
	tree->recalculate();
}
bool SwapMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return 	IsBinary()(node);
}
