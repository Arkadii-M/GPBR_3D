#pragma once
#ifndef FUNCTION_INFO_H
#define FUNCTION_INFO_H

class AdditionalInfo {
protected:
	const double apply_prob;
public:
	AdditionalInfo(double prob);
	~AdditionalInfo() = default;

	double getApplyProbability() const;

};
#endif // !FUNCTION_INFO_H
