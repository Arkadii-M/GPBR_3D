#include "ConstMutation.h"
#include "../GP/ConstantNode.h"

ConstantMutation::ConstantMutation(double a, double b, double scale, double prob):
	GeneticOpretator(prob),
	a(a),
	b(b),
	scale(scale)
{
	assert(a < b);
	assert(scale > 0);
}

void ConstantMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();

	// If tree has only one node(root) generate new tree.
	if (tree->getHeight() == 0)
		return;

	auto terminals = tree->filterNodes(NodeFilter(
		[](NodeFilter::node_arg arg)
		{
			return IsLeaf()(arg) && IsNumber()(arg);
		}
	));

	if (terminals.empty())
		return;

	auto observer = tree->getNodeObserver(*Random::get(terminals.begin(), terminals.end()));


	double fit_scale = scale*individuum.lock()->getFintness();
	double rand_value = Random::get<double>(a- fit_scale, b+ fit_scale);

	NodeObserver::SwapSubTrees(observer,
		std::make_unique<ConstantNode>(std::any_cast<double>(observer->getValue()) + rand_value));
	
	tree->recalculate();
}