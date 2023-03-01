#pragma once
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "IExpressionNode.h"
#include <format>
#include <functional>

typedef std::function<arma::dmat(const arma::dmat&, const arma::dmat&)> dmatBinaryFunc;
typedef std::function<arma::dcube(const arma::dmat& x,const arma::dmat& y,const arma::dcube& dx,const arma::dcube& dy)> dmatBinaryDerivative;
class BinaryNode : public IExpressionNode
{
private:
	const dmatBinaryFunc func;
	const dmatBinaryDerivative dfunc;
public:
	//BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right);
	BinaryNode(dmatBinaryFunc func, dmatBinaryDerivative dfunc, std::string node_name, std::unique_ptr<IExpressionNode> left, std::unique_ptr<IExpressionNode> right);

	BinaryNode(const BinaryNode& node);

	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;

	virtual std::string toString() const override;


	// Inherited via IExpressionNode
	virtual std::unique_ptr<IExpressionNode> clone() override;


	// Inherited via IExpressionNode
	virtual TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo) override;

};

#endif //UNARY_NODE_H