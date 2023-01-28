#pragma once
#ifndef UNARY_FUNCTION_H
#define UNARY_FUNCTION_H
#include <functional>
#include <string>

typedef std::function<double(double)> dUFunc;
class UnaryFunction
{
protected:
	const dUFunc func;
	const dUFunc d_func;
	const dUFunc dd_func;
public:
	const std::string func_name;
public:
	UnaryFunction(std::string func_name,dUFunc func, dUFunc d_func, dUFunc dd_func);
	UnaryFunction(dUFunc func,std::string func_name);

	virtual double operator()(double val) const = 0;
	virtual double firstDerivative(double val) const =0;
	virtual double secondDerivative(double val) const=0;
};

#endif //UNARY_FUNCTION_H