#include "../GP/GeneticOperator.h"
#include "../GP/TreeGenerator.h"
#include "../GP/random.hpp"
#include "NodeFilterDefines.h"

#ifndef MUTATE_NODE_REPLACE_H
#define MUTATE_NODE_REPLACE_H


using Random = effolkronium::random_static;

class NodeReplaceMutation :public GeneticOpretator // WMinMaxHC - with minimum and maximum height control
{
private:
	std::shared_ptr<TreeGenerator> tree_gen;
public:
	NodeReplaceMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob = 1.0);
	void apply(std::weak_ptr<Individuum> individuum) override;
};
#endif // !MUTATE_NODE_REPLACE_H
