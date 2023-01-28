#include "BinaryFunction.h"

BinaryFunction::BinaryFunction(std::string func_name, dBFunc func, dBFunc d_func, dBFunc dd_func):
	func(func),
	d_func(d_func),
	dd_func(dd_func),
	func_name(func_name)
{
}

BinaryFunction::BinaryFunction(dBFunc func, std::string func_name):
	func(func),
	d_func(NULL),
	dd_func(NULL),
	func_name(func_name)
{
}