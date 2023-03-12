#pragma once
#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

#include <armadillo>

class ErrorFunction
{
public:
	virtual double evaluate(const arma::dcolvec& exact, const  arma::dcolvec& approx); // evaluate the error
	virtual arma::dcube evaluateDerivative(const arma::dcolvec& exact, const  arma::dcolvec& approx, const arma::dcube& derivatives); // evaluate derivatives
};



#endif // !ERROR_FUNCTION_H
