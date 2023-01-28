#include "FunctionInfo.h"

AdditionalInfo::AdditionalInfo(double prob):
	apply_prob(prob)
{
}

double AdditionalInfo::getApplyProbability() const
{
	return apply_prob;
}
