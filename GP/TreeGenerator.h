#pragma once
#ifndef TREE_GENERATOR_H
#define TREE_GENERATOR_H
#include <vector>
#include <string>
#include <memory>
#include "GpData.h"
#include "ExpressionTree.h"



class TreeGenerator
{
protected:
	std::shared_ptr<GpData> data;
public:
	TreeGenerator(std::shared_ptr<GpData>& dat);

	virtual std::unique_ptr<ExpressionTree> generateTree() = 0;
	virtual std::unique_ptr<ExpressionTree> generateTree(uint h) = 0;
	virtual std::unique_ptr<ExpressionTree> generateTree(uint max_h, uint min_h) = 0;

	virtual std::unique_ptr<IExpressionNode> generateSubTree() = 0;
	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint h) = 0;
	virtual std::unique_ptr<IExpressionNode> generateSubTree(uint max_h, uint min_h) = 0;
};

#endif //TREE_GENERATOR_H
