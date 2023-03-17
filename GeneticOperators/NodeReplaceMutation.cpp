#include "NodeReplaceMutation.h"

NodeReplaceMutation::NodeReplaceMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob):
	GeneticOpretator(prob),
	tree_gen(tree_gen)
{
}

void NodeReplaceMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();
	// If tree has only one node(root) generate new tree.
	if (tree->getHeight() == 0)
		return;

	auto nodes = tree->filterNodes(NodeFilter(
		[](NodeFilter::node_arg arg)
		{
			return 	NotRoot()(arg);
		}
	));

	auto observer = tree->getNodeObserver(*Random::get(nodes.begin(), nodes.end()));


	if (observer->isLeaf())
	{
		NodeObserver::ReplaceNodes(observer, tree_gen->generateTerminal());
		tree->recalculate();
		return;
	}
	if (observer->isUnary())
	{
		NodeObserver::ReplaceNodes(observer, tree_gen->generateUnary());
		tree->recalculate();
		return;
	}
	if (observer->isBinary())
	{
		NodeObserver::ReplaceNodes(observer, tree_gen->generateBinary());
		tree->recalculate();
		return;
	}
}