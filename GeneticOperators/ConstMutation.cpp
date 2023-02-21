#include "ConstMutation.h"
#include "../GP/ConstantNode.h"

ConstantMutation::ConstantMutation(arma::uword n_rows, arma::uword n_cols,double prob):
	GeneticOpretator(prob),
	n_rows(n_rows),
	n_cols(n_cols)
{
}

void ConstantMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();

	// If tree has only one node(root) generate new tree.
	if (tree->getHeight() == 0)
		return;

	auto nodes_list = tree->filterNodesIdexes(std::make_unique<ConstantMutation::Filter>());

	if (nodes_list.size() == 0)// no node to select
		return;

	uint rand_node = *Random::get(nodes_list.begin(), nodes_list.end());

	auto observer = tree->getNodeObserver(rand_node);
	//ExpressionTree::NodeObserve::SwapSubTrees(observer,
	//	std::make_unique<ConstantNode>(std::stod(observer->getName()) + Random::get<double>(-1.0, 1.0), n_rows, n_cols));
	ExpressionTree::NodeObserve::SwapSubTrees(observer,
		std::make_unique<ConstantNode>(std::stod(observer->getName()) + Random::get<double>(-1.0, 1.0)));
	tree->recalculate();
}
bool ConstantMutation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return 	IsLeaf()(node) && IsNumber()(node);
}
