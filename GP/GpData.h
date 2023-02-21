#pragma once
#include "BinaryNode.h"
#include "UnaryNode.h"
#include <set>
#include "GpItem.h"
#ifndef GP_DATA_H
#define GP_DATA_H

class GpData
{
public:
	typedef GpItem<dmatBinaryFunc> BinaryItem;
	typedef GpItem<dmatUnaryFunc> UnaryItem;
	typedef GpItem<std::string>	VariableItem;
	typedef GpItem<double> ConstItem;


	typedef std::set<GpItem<dmatBinaryFunc>> Bset;
	typedef std::set<GpItem<dmatUnaryFunc>> Uset;
	typedef std::set<GpItem<std::string>> Vset;
	typedef std::set<GpItem<double>> Cset;

private:
	Bset binary_functions;
	Uset unary_functions;
	Vset variables;
	Cset constants;
	const arma::uword n_rows;
	const arma::uword n_cols;
public:
	GpData(Bset bfuncs, Uset ufuncs, Vset vars, Cset consts, arma::uword n_rows = 0, arma::uword n_cols = 0);

	Bset getBinaryFunction() const;
	Uset getUnaryFunction() const;
	Vset getVariables() const;
	Cset getConstants() const;

	arma::uword getEvalNRows() const;
	arma::uword getEvalNCols() const;
};

#endif // !GP_DATA_H
