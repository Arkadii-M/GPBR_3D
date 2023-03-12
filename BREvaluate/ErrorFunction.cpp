#include "ErrorFunction.h"


double ErrorFunction::evaluate(const arma::dcolvec& exact, const  arma::dcolvec& approx)
{
	throw std::exception("Not implemented");
}
arma::dcube ErrorFunction::evaluateDerivative(const arma::dcolvec& exact, const  arma::dcolvec& approx, const arma::dcube& derivatives)
{
	throw std::exception("Not implemented");
}