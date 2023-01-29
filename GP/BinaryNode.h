#pragma once
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "IExpressionNode.h"
#include <format>
#include <functional>

typedef std::function<arma::dmat(const arma::dmat&, const arma::dmat&)> dmatBinaryFunc;
class BinaryNode : public IExpressionNode
{
private:
	const dmatBinaryFunc func;
public:
	//BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right);
	BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode> left, std::unique_ptr<IExpressionNode> right);

	BinaryNode(const BinaryNode& node);

	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;

	virtual std::string toString() const override;


	// Inherited via IExpressionNode
	virtual std::unique_ptr<IExpressionNode> clone() override;

};

#endif //UNARY_NODE_H