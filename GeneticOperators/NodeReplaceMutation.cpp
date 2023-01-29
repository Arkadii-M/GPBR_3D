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


	std::vector<uint> nodes_list = tree->filterNodesIdexes(std::make_unique< NodeReplaceMutation::Filter>());
	uint rand_node = *Random::get(nodes_list.begin(), nodes_list.end());
	auto observer = tree->getNodeObserver(rand_node);

	if (observer->isLeaf())
	{
		ExpressionTree::NodeObserve::ReplaceNodes(observer, tree_gen->generateTerminal());
		tree->recalculate();
		return;
	}
	if (observer->isUnary())
	{
		ExpressionTree::NodeObserve::ReplaceNodes(observer, tree_gen->generateUnary());
		tree->recalculate();
		return;
	}
	if (observer->isBinary())
	{
		ExpressionTree::NodeObserve::ReplaceNodes(observer, tree_gen->generateBinary());
		tree->recalculate();
		return;
	}
}
bool NodeReplaceMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return NotRoot()(node);
}
