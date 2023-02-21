#pragma once
#include <memory>
#include "../GP/GpData.h"
#include "../GP/TreeGenerator.h"
#include "../GP/random.hpp"
#include <numeric>      // std::accumulate

#ifndef PTC_1_H
#define PTC_1_H

using Random = effolkronium::random_static;

class PTC_1_Generator : public TreeGenerator
{
private:
	uint expect_size;
	uint max_h;
	double prob_p; // probability of choosing a nonterminal over a terminals in order to produce a tree with an expected size;
public:
	PTC_1_Generator(std::shared_ptr<GpData>& dat,uint expect_size, uint max_h);



	// Inherited via TreeGenerator
	virtual std::unique_ptr<ExpressionTree> generateTree() override;

	virtual std::unique_ptr<ExpressionTree> generateTree(uint h) override;

	virtual std::unique_ptr<ExpressionTree> generateTree(uint max_h, uint min_h) override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree() override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint h) override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint max_h, uint min_h) override;

private:
	std::unique_ptr<IExpressionNode> ptc1Alg(uint ltc);

	std::unique_ptr<IExpressionNode> createTerminal(uint ltc);
	std::unique_ptr<IExpressionNode> createFunctional(uint ltc);

};


#endif // PTC_1_H