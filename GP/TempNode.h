#pragma once
#ifndef TEMP_NODE_H
#define TEMP_NODE_H
#include "../GPBR_3D/IExpressionNode.h"


class TempNode :public IExpressionNode
{
public:
	TempNode();
	// Inherited via IExpressionNode
	virtual arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi) override;
	virtual std::unique_ptr<IExpressionNode> clone() override;
	virtual std::string toString() const override;
};


#endif // !TEMP_NODE_H

