#pragma once
#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "IExpressionNode.h"
#include <format>
#include <functional>

typedef std::function<arma::dmat(const arma::dmat&)> dmatUnaryFunc;
typedef std::function<arma::dmat(const arma::dmat& x,const arma::dmat& dx)> dmatUnaryDerivative;
class UnaryNode : public IExpressionNode
{
private:
	const dmatUnaryFunc func;
	const dmatUnaryDerivative dfunc;
public:
	//UnaryNode(dmatUnaryFunc func,std::string node_name, std::unique_ptr<IExpressionNode>& left);
	UnaryNode(dmatUnaryFunc func, dmatUnaryDerivative dfunc, std::string node_name, std::unique_ptr<IExpressionNode> left);
	UnaryNode(const UnaryNode& node);


	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;

	virtual std::string toString() const override;


	// Inherited via IExpressionNode
	virtual std::unique_ptr<IExpressionNode> clone() override;


	// Inherited via IExpressionNode
	//virtual TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo) override;
	virtual TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivative::PartialDerivativeStrategy strategy) override;
	virtual std::any getValue() const override;

};

#endif //UNARY_NODE_H