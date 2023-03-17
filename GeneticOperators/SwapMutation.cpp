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
	auto binary_nodes = tree->filterNodes(NodeFilter(
		[](NodeFilter::node_arg arg)
		{
			return arg->isBinary();
		}
	));

	if (binary_nodes.empty())
		return;

	auto observer = tree->getNodeObserver(*Random::get(binary_nodes.begin(), binary_nodes.end()));

	auto left = observer->getLeft();
	auto right = observer->getRight();
	NodeObserver::SwapSubTrees(left, right);
	tree->recalculate();
}