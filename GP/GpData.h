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
	using dmatBinaryDerivative = 
		std::function<arma::dmat(
		const arma::dmat& x,
		const arma::dmat& y,
		const arma::dmat& dx,
		const arma::dmat& dy)>;

	using dmatUnaryDerivative = 
		std::function<arma::dmat(
		const arma::dmat& x,
		const arma::dmat& dx)>;

	using BinaryItem = GpItem<dmatBinaryFunc, dmatBinaryDerivative>;
	using UnaryItem = GpItem<dmatUnaryFunc, dmatUnaryDerivative>;
	using VariableItem =  GpItem<std::string>;
	using ConstItem =  GpItem<double>;


	using Bset = std::set<BinaryItem>;
	using Uset = std::set<UnaryItem>;
	using Vset = std::set<VariableItem>;
	using Cset = std::set<ConstItem>;

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
