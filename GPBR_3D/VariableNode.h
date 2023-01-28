#pragma once
#ifndef VARIABLE_NODE_H
#define VARIABLE_NODE_H

#include "IExpressionNode.h"
#include <format>


class VariableNode : public IExpressionNode
{
public:
	VariableNode(std::string node_name);
	VariableNode(const VariableNode& node);

	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;

	virtual std::string toString() const override;


	// Inherited via IExpressionNode
	virtual std::unique_ptr<IExpressionNode> clone() override;

};

#endif //VARIABLE_NODE_H