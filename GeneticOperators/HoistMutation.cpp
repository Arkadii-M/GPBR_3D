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

	auto nodes = tree->filterNodes(NodeFilter(
		[&](NodeFilter::node_arg arg)
		{
			return NotRoot()(arg) && MinHeight(min_height)(arg);
		}
	));
	if (nodes.empty())// no node to select
		return;

	auto observer = tree->getNodeObserver(* Random::get(nodes.begin(), nodes.end()));

	individuum.lock()->setTree(std::make_unique<ExpressionTree>(observer->subTreeCopy()));
}