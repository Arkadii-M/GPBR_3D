#ifndef ONE_POINT_CROSSOVER_H
#define ONE_POINT_CROSSOVER_H
#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilter.h"
#include <algorithm>

using Random = effolkronium::random_static;

class OnePointCrossover :public GeneticOpretator
{
	using common_pair = std::pair<uint, uint>;
public:
	OnePointCrossover(double prob = 1.0);
	void apply(std::weak_ptr<Individuum> first, std::weak_ptr<Individuum> second) override;

private:
	void findCommon(std::unique_ptr<ExpressionTree::NodeObserve> first_observer, std::unique_ptr<ExpressionTree::NodeObserve> second_observer, std::vector<common_pair>& common);
	//void CrossoveTrees(std::unique_ptr<Tree>& first_tree, std::unique_ptr<Tree>& second_tree);

	//CommonTreeFinder common_finder;
};

#endif // !ONE_POINT_CROSSOVER_H