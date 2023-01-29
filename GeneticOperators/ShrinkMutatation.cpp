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

	auto nodes_list = tree->filterNodesIdexes(std::make_unique<ShrinkMutation::Filter>());

	uint rand_node = *Random::get(nodes_list.begin(), nodes_list.end());

	auto observer = tree->getNodeObserver(rand_node);
	auto rand_terminal = tree_gen->generateTerminal();
	auto terminal = std::make_unique<ExpressionTree::NodeObserve>(rand_terminal);
	ExpressionTree::NodeObserve::SwapSubTrees(observer, terminal);
	tree->recalculate();
}
bool ShrinkMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return 	NotRoot()(node);
}
