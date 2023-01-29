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
	std::unique_ptr<IExpressionNode> randTree(uint ltc);

	std::unique_ptr<IExpressionNode> createTerminal(uint ltc);
	std::unique_ptr<IExpressionNode> createFunctional(uint ltc);

public:
	// Inherited via TreeGenerator
	virtual std::unique_ptr<IExpressionNode> generateTerminal() override;

	virtual std::unique_ptr<IExpressionNode> generateUnary() override;

	virtual std::unique_ptr<IExpressionNode> generateBinary() override;

};


#endif // FULL_GROW_H