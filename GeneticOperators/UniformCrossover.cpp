#include "UniformCrossover.h"

UniformCrossover::UniformCrossover(double replace_prob,double prob):
	GeneticOpretator(prob),
	replace_prob(replace_prob)
{
	if (!(replace_prob > 0 && replace_prob < 1.0))
		throw std::invalid_argument(std::format("Replace probabilty must be in (0,1) but {} was given.",replace_prob));
}

void UniformCrossover::apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second)
{
	auto& first_tree = first.lock()->getTree();
	auto& second_tree = second.lock()->getTree();
	commonCrossover(first_tree->getRootObserver(), second_tree->getRootObserver());
	first_tree->recalculate();
	second_tree->recalculate();
}

void UniformCrossover::commonCrossover(std::unique_ptr<NodeObserver> first_observer, std::unique_ptr<NodeObserver> second_observer)
{
	if (first_observer->isNull() || second_observer->isNull())
		return;

	if (first_observer->getNum() != 1 && second_observer->getNum() != 1)
	{
		if (Random::get<bool>(replace_prob))// replace nodes with predefined probability
		{
			if (first_observer->isLeaf() || second_observer->isLeaf()) // if one of the tree is leaf swap subtrees and return
			{
				NodeObserver::SwapSubTrees(first_observer, second_observer);
				return;
			}
			if (first_observer->isBinary() && second_observer->isBinary()
				|| first_observer->isUnary() && second_observer->isUnary())// both nodes are the same type so replace them
			{
				NodeObserver::ReplaceNodes(first_observer, second_observer);
			}
			// Else just swap subtrees
			NodeObserver::SwapSubTrees(first_observer, second_observer);

		}
	}
	commonCrossover(first_observer->getLeft(), second_observer->getLeft());
	commonCrossover(first_observer->getRight(), second_observer->getRight());
}
