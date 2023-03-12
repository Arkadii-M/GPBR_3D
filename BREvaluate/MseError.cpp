#include "MseError.h"

double MseError::evaluate(const arma::dcolvec& exact, const  arma::dcolvec& approx)
{
	return sum(pow(approx - exact, 2))/(double)exact.n_elem;
}
arma::dcube MseError::evaluateDerivative(const arma::dcolvec& exact, const  arma::dcolvec& approx, const arma::dcube& derivatives)
{
	return 2*arma::sum((approx - exact) % derivatives.each_slice(), 0); // sum of column of each slices
}