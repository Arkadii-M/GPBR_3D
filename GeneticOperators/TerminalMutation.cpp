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


	auto terminals = tree->filterNodesIdexes(std::make_unique <TerminalMutation::Filter>());
	uint rand_terminal = *Random::get(terminals.begin(), terminals.end());
	auto rand_observer = tree->getNodeObserver(rand_terminal);
	ExpressionTree::NodeObserve::SwapSubTrees(rand_observer, tree_gen->generateTerminal());
	tree->recalculate();
}

bool TerminalMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return 	IsLeaf()(node);
}