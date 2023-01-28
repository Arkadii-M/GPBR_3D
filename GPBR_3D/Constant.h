#pragma once
#ifndef CONSTANT_H
#define CONSTANT_H
#include <functional>
#include <string>

class Constant
{
public:
	const double value;
public:
	Constant(double value);

	virtual double firstDerivative() = 0;
	virtual double secondDerivative() = 0;
};

#endif //CONSTANT_H