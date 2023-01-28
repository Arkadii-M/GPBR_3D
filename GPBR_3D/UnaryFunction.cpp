#include "UnaryFunction.h"

UnaryFunction::UnaryFunction(std::string func_name, dUFunc func, dUFunc d_func, dUFunc dd_func):
	func(func),
	d_func(d_func),
	dd_func(dd_func),
	func_name(func_name)
{
}

UnaryFunction::UnaryFunction(dUFunc func, std::string func_name):
	func(func),
	d_func(NULL),
	dd_func(NULL),
	func_name(func_name)
{
}
//
//double UnaryFunction::operator()(double val) const
//{
//	return func(val);
//}
//
//double UnaryFunction::firstDerivative(double val) const
//{
//	return d_func(val);
//}
//
//double UnaryFunction::secondDerivative(double val) const
//{
//	return dd_func(val);
//}
