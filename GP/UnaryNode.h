#pragma once
#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "IExpressionNode.h"
#include <format>
#include <functional>

typedef std::function<arma::dmat(const arma::dmat&)> dmatUnaryFunc;
class UnaryNode : public IExpressionNode
{
private:
	const dmatUnaryFunc func;
public:
	//UnaryNode(dmatUnaryFunc func,std::string node_name, std::unique_ptr<IExpressionNode>& left);
	UnaryNode(dmatUnaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode> left);
	UnaryNode(const UnaryNode& node);


	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;

	virtual std::string toString() const override;


	// Inherited via IExpressionNode
	virtual std::unique_ptr<IExpressionNode> clone() override;

};

#endif //UNARY_NODE_H