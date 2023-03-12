#pragma once
#ifndef MSE_ERROR_FUNCTION
#define MSE_ERROR_FUNCTION
#include "ErrorFunction.h"

class MseError : public ErrorFunction
{
public:
	using uint = unsigned int;
	virtual double evaluate(const arma::dcolvec& exact, const  arma::dcolvec& approx) override; // evaluate the error
	virtual arma::dcube evaluateDerivative(const arma::dcolvec& exact, const  arma::dcolvec& approx, const arma::dcube& derivatives) override; // evaluate derivatives
};



#endif // MSE_ERROR_FUNCTION
