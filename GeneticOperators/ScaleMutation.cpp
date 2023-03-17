#include "ScaleMutation.h"

ScaleMutation::ScaleMutation(std::shared_ptr<GpData> gp_data,double scale, double prob):
	GeneticOpretator(prob),
	gp_data(gp_data),
	scale(scale)
{

	// Generate multiply node
	auto binary_funcs = gp_data->getBinaryFunction();

	
	auto found = std::find_if(binary_funcs.begin(), binary_funcs.end(),
		[](const GpData::BinaryItem& item) {
			return item.getName() == "*";
		});
	if (found == binary_funcs.end())
		throw std::exception("Given binary function set does not contain multiply function");
	multiply_item = *found;
}

void ScaleMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();
	// This mutation is accept just terminal (height 0)
	 
	// Generate scale to mutate current tree
	double fit_scale = scale * individuum.lock()->getFintness();
	double rand_value = Random::get<double>(1.0 - fit_scale, 1.0 + fit_scale);




	// Get root of an old tree
	auto old_root_observer = tree->getRootObserver();
	if (checkRootAndMutateIfNeed(old_root_observer, fit_scale))
	{
		tree->recalculate();
		return;
	}

	// Generate root with multiply function
	//auto new_tree = std::make_unique<ExpressionTree>(
	//	std::make_unique<BinaryNode>(
	//		multiply_item.getItem(),
	//		multiply_item.getDerivative(),
	//		multiply_item.getName(),
	//		std::make_unique<TempNode>(),
	//		std::make_unique<ConstantNode>(rand_value)));

	auto new_tree = std::make_unique<ExpressionTree>(
	std::make_unique<BinaryNode>(
		multiply_item.getItem(),
		multiply_item.getDerivative(),
		multiply_item.getName(),
		nullptr,
		std::make_unique<ConstantNode>(rand_value)));



	// Get observer to the node to change
	auto new_root_observer = new_tree->getRootObserver();
	auto left_of_multiply_observer = new_root_observer->getLeft();

	NodeObserver::SwapSubTrees(left_of_multiply_observer, old_root_observer);

	new_tree->recalculate();
	individuum.lock()->setTree(std::move(new_tree));
}
bool ScaleMutation::checkRootAndMutateIfNeed(std::unique_ptr<NodeObserver>& root_observer, const double fit_scale)
{
	if (root_observer->getName() == multiply_item.getName())// if the root is already multiply
	{
		auto left = root_observer->getLeft();
		if (left->isConstant())// adjust constant
		{
			adjustConstant(left, fit_scale);
			return true;
		}

		auto right = root_observer->getRight();
		if (right->isConstant())// adjust constant
		{
			adjustConstant(right, fit_scale);
			return true;
		}
	}
	return false;
}

void ScaleMutation::adjustConstant(std::unique_ptr<NodeObserver>& const_observer, const double fit_scale)
{
	if (Random::get<bool>())
	{
		//NodeObserver::SwapSubTrees(const_observer,
		//	std::make_unique<ConstantNode>(std::stod(const_observer->getName()) + fit_scale));
		NodeObserver::SwapSubTrees(const_observer,
			std::make_unique<ConstantNode>(std::any_cast<double>(const_observer->getValue()) + fit_scale));
	}
	else
	{
		NodeObserver::SwapSubTrees(const_observer,
			std::make_unique<ConstantNode>(std::any_cast<double>(const_observer->getValue()) + fit_scale));
		//NodeObserver::SwapSubTrees(const_observer,
		//	std::make_unique<ConstantNode>(std::stod(const_observer->getName()) - fit_scale));
	}

}