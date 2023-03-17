#include "ShrinkMutatation.h"

ShrinkMutation::ShrinkMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob):
	GeneticOpretator(prob),
	tree_gen(tree_gen)
{
}

void ShrinkMutation::apply(std::weak_ptr<Individuum> individuum)
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

	auto rand_terminal = tree_gen->generateTerminal();
	auto terminal = std::make_unique<NodeObserver>(rand_terminal);
	
	NodeObserver::SwapSubTrees(observer, terminal);
	tree->recalculate();
}
