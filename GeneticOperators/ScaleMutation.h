#pragma once
#ifndef SCALE_MUTATION_H
#define SCALE_MUTATION_H


#include "../GP/GeneticOperator.h"
#include "../GP/random.hpp"
#include "NodeFilterDefines.h"
#include "../GP/TreeGenerator.h"
#include "../GP/GpData.h"

using Random = effolkronium::random_static;

class ScaleMutation :public GeneticOpretator // Select and return random subtree
{
private:
	const double scale;
	std::shared_ptr<GpData> gp_data;
	GpData::BinaryItem multiply_item;
public:
	ScaleMutation(std::shared_ptr<GpData> gp_data,double scale, double prob = 1.0);
	virtual void apply(std::weak_ptr<Individuum> individuum) override;

private:
	bool checkRootAndMutateIfNeed(std::unique_ptr<NodeObserver>& root_observer,const double fit_scale);
	void adjustConstant(std::unique_ptr<NodeObserver>& const_observer, const double fit_scale);
};

#endif // !SCALE_MUTATION_H
