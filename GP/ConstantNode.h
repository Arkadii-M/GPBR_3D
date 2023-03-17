#pragma once
#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include <format>
#include "IExpressionNode.h"


class ConstantNode : public IExpressionNode
{
private:
	const double value;
	//const arma::dmat ConstMatrix;
public:
	//ConstantNode(double value,arma::uword n_row,arma::uword n_col);
	ConstantNode(double value);
	ConstantNode(const ConstantNode& node);

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

#endif //CONSTANT_NODE_H