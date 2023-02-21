#pragma once
#ifndef TREE_GENERATOR_H
#define TREE_GENERATOR_H
#include <vector>
#include <string>
#include <memory>
#include "GpData.h"
#include "ExpressionTree.h"
#include "random.hpp"
#include "VariableNode.h"
#include "ConstantNode.h"



using Random = effolkronium::random_static;
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

	virtual std::unique_ptr<IExpressionNode> generateTerminal();
	virtual std::unique_ptr<IExpressionNode> generateFunctional();

	virtual std::unique_ptr<IExpressionNode> generateConstant();
	virtual std::unique_ptr<IExpressionNode> generateVariable();
	virtual std::unique_ptr<IExpressionNode> generateUnary();
	virtual std::unique_ptr<IExpressionNode> generateBinary();



};

#endif //TREE_GENERATOR_H
