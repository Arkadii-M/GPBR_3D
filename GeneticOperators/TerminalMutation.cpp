#include "TerminalMutation.h"

TerminalMutation::TerminalMutation(std::shared_ptr<TreeGenerator> tree_gen,double prob):
	GeneticOpretator(prob),
	tree_gen(tree_gen)
{
}

void TerminalMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();

	if (tree->getHeight() == 0)
		return;

	auto terminals = tree->filterNodes(NodeFilter(
		[](NodeFilter::node_arg arg)
		{
			return arg->isLeaf();
		}
	));
	if (terminals.empty())
		return;

	auto rand_observer = tree->getNodeObserver(*Random::get(terminals.begin(), terminals.end()));

	NodeObserver::SwapSubTrees(rand_observer, tree_gen->generateTerminal());
	tree->recalculate();
}
