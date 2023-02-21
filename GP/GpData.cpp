#include "GpData.h"

GpData::GpData(Bset bfuncs, Uset ufuncs, Vset vars, Cset consts,
	arma::uword n_rows, arma::uword n_cols):
	binary_functions(bfuncs),
	unary_functions(ufuncs),
	variables(vars),
	constants(consts),
	n_rows(n_rows),
	n_cols(n_cols)
{
}

GpData::Bset GpData::getBinaryFunction() const
{
	return binary_functions;
}

GpData::Uset GpData::getUnaryFunction() const
{
	return unary_functions;
}

GpData::Vset GpData::getVariables() const
{
	return variables;
}

GpData::Cset GpData::getConstants() const
{
	return constants;
}

arma::uword GpData::getEvalNRows() const
{
	return n_rows;
}

arma::uword GpData::getEvalNCols() const
{
	return n_cols;
}
