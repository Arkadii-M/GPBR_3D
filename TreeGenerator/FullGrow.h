#pragma once
#include <memory>
#include "../GP/GpData.h"
#include "../GP/TreeGenerator.h"
#include "../GP/random.hpp"

#ifndef FULL_GROW_H
#define FULL_GROW_H

using Random = effolkronium::random_static;

class FullGrowGenerator : public TreeGenerator
{
private:
	uint min_height;
	uint max_height;
	uint terminal_count;
	uint functional_count;
	uint curr_height;
public:
	FullGrowGenerator(std::shared_ptr<GpData>& dat, uint min_h, uint max_h);



	// Inherited via TreeGenerator
	virtual std::unique_ptr<ExpressionTree> generateTree() override;

	virtual std::unique_ptr<ExpressionTree> generateTree(uint h) override;

	virtual std::unique_ptr<ExpressionTree> generateTree(uint max_h, uint min_h) override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree() override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint h) override;

	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint max_h, uint min_h) override;

private:
	std::unique_ptr<IExpressionNode> randTree(uint ltc,uint curr_h);

	std::unique_ptr<IExpressionNode> createTerminal(uint ltc, uint curr_h);
	std::unique_ptr<IExpressionNode> createFunctional(uint ltc, uint curr_h);

};


#endif // FULL_GROW_H