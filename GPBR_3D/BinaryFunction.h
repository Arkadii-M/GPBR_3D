#pragma once
#ifndef BINARY_FUNCTION_H
#define BINARY_FUNCTION_H
#include <functional>
#include <string>

typedef std::function<double(double,double)> dBFunc;
class BinaryFunction
{
protected:
	const dBFunc func;
	const dBFunc d_func;
	const dBFunc dd_func;
public:
	const std::string func_name;
public:
	BinaryFunction(std::string func_name, dBFunc func, dBFunc d_func, dBFunc dd_func);
	BinaryFunction(dBFunc func, std::string func_name);

	virtual double operator()(double x,double y) const = 0;
	virtual double firstDerivative(double x, double y) const = 0;
	virtual double secondDerivative(double x, double y) const = 0;
};

#endif //BINARY_FUNCTION_H