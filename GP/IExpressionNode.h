#pragma once
#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

#include <string>
#include <memory>
#include <armadillo>
#include <ostream>
#include <any>
#include "PartialTreeDerivative.h"
typedef unsigned int uint;
class IExpressionNode
{
protected:
	std::unique_ptr<IExpressionNode> left, right;
	const std::string node_name;
	uint order_number;
	uint height;
	uint depth;

public:
	IExpressionNode(std::string node_name);
	//IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode> & left);
	//IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right);
	IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode> left);
	IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode> left, std::unique_ptr<IExpressionNode> right);
	IExpressionNode(const IExpressionNode& node);
	IExpressionNode(const std::unique_ptr<IExpressionNode>& node);

	virtual ~IExpressionNode() = default;

	bool isLeaf() const;

	uint getNum() const;
	void setNum(uint num);


	uint getDepth() const;
	void setDepth(uint depth);

	uint getHeight() const;
	void setHeight(uint h);

	std::unique_ptr<IExpressionNode>& getLeftSon();
	std::unique_ptr<IExpressionNode>& getRightSon();

	virtual std::any getValue() = 0;

	void setLeftSon(std::unique_ptr<IExpressionNode> rhs);
	void setRightSon(std::unique_ptr<IExpressionNode> rhs);

	// evaluete the tree expression
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) = 0;
	virtual TreeDerivative autoDiffReverse(const arma::dmat& thetha,const arma::dmat& phi,const TreeDerivativeInfo & dinfo) = 0; // Evaluates function and partial derivatives in O(tree_size)

	virtual std::unique_ptr<IExpressionNode> clone() = 0;
	virtual std::string toString() const = 0;
	std::string getName() const;

	static bool Equal(const IExpressionNode& first, const IExpressionNode& second);
	friend std::ostream& operator<<(std::ostream& os, const std::unique_ptr<IExpressionNode>& node);
};

#endif //EXPRESSION_NODE_H