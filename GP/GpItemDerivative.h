#pragma once
#ifndef GP_ITEM_DERIVATIVE_H
#define GP_ITEM_DERIVATIVE_H
#include <string>

template<typename Type>
class GpItemDerivative {
private:
	Type item;
	const std::string name;
	const double select_proba;
	double cumulative_prob;
public:
};


#endif // !GP_ITEM_DERIVATIVE_H
