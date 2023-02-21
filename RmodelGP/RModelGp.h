#pragma once
#include <iostream>
#ifndef R_MODEL_GP_H
#define R_MODEL_GP_H

#include "../GP/Gp.h"
#include "../GP/GeneticOperator.h"
#include "RModelSelector.h"
#include "../SolutionProcessor/SolutionProcessor.h"

class RmodelGp :public GP
{
private:
	std::vector<std::unique_ptr<GeneticOpretator>> mutate_operators;
	std::vector<std::pair<double, int>> mutate_cumulative;

	std::vector<std::unique_ptr<GeneticOpretator>> crossove_operators;
	std::vector<std::pair<double, int>> crossove_cumulative;

	std::unique_ptr<RModelSelector> selector;
	std::unique_ptr<SolutionProcesser> processor;

public:
	//RmodelGp(std::unique_ptr<Evaluator> ev,
	//	std::shared_ptr<TreeGenerator> gen,
	//	std::unique_ptr<RModelSelector> select,
	//	std::vector<std::unique_ptr< GeneticOpretator>>& mut_operators,
	//	std::vector<std::unique_ptr< GeneticOpretator>>& cross_operators,
	//	std::unique_ptr<SolutionProcesser> pro
	//);
	RmodelGp(std::unique_ptr<Evaluator> ev,
		std::shared_ptr<TreeGenerator> gen,
		std::unique_ptr<RModelSelector> select,
		std::vector<std::unique_ptr< GeneticOpretator>>& mut_operators,
		std::vector<std::unique_ptr< GeneticOpretator>>& cross_operators,
		std::unique_ptr<SolutionProcesser> processor,
		uint max_n_change,
		double delta
	);

	virtual bool execute(uint iter) override;
	virtual void generatePopulation(uint pop_size) override;


private:
	void executeOne();
	void evaluatePopulation();
};

#endif //R_MODEL_GP_H