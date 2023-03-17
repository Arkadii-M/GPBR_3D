#include "OnePointCrossover.h"

OnePointCrossover::OnePointCrossover(double prob):
	GeneticOpretator(prob)
{
}

void OnePointCrossover::apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second)
{
	auto& first_tree = first.lock()->getTree();
	auto& second_tree = second.lock()->getTree();
	std::vector<common_pair> common = std::vector<common_pair>();

	findCommon(first_tree->getRootObserver(), second_tree->getRootObserver(),common);

	if (common.size() == 0)
		return;

	auto rand_pair = *Random::get(common.begin(), common.end());

	auto first_node = first_tree->getNodeObserver(rand_pair.first);
	auto second_node = second_tree->getNodeObserver(rand_pair.second);

	ExpressionTree::SwapSubTress(first_tree, second_tree, first_node, second_node);
}

void OnePointCrossover::findCommon(
	std::unique_ptr<NodeObserver> first_observer, 
	std::unique_ptr<NodeObserver> second_observer,
	std::vector<common_pair>& common)
{
	if (first_observer->isNull() || second_observer->isNull())
		return;
	// skip roots
	if (first_observer->getNum() != 1 && first_observer->getNum() != 1)
	{
		common.emplace_back(first_observer->getNum(), second_observer->getNum());
	}

	findCommon(first_observer->getLeft(), second_observer->getLeft(), common);
	findCommon(first_observer->getRight(), second_observer->getRight(), common);
}
