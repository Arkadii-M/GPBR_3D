#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H
#include <functional>
#include <string>

class Variable
{
public:
	const std::string var_name;
public:
	Variable(std::string var_name);

	virtual double firstDerivative(std::string diff_var)const  = 0;
	virtual double secondDerivative() const = 0;
};

#endif //VARIABLE_H