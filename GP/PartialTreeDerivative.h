#pragma once
#include <vector>
#include <armadillo>
#ifndef PARTIAL_DERIVATIVE_H
#define PARTIAL_DERIVATIVE_H

typedef unsigned int uint;
class TreeDerivativeInfo
{
private:
	std::vector<uint> diff_ids;
public:
	TreeDerivativeInfo(std::vector<uint> ids);
	bool inDiffIdArray(const uint id) const;
	uint getNelements() const;
};
class TreeDerivative
{
private:
	const arma::dmat x;
	const arma::dcube dx;

public:
	TreeDerivative(arma::dmat& x, arma::dcube& dx);

	const arma::dmat& getElement() const;
	const arma::dcube& getDerivative() const;

};

#endif // !PARTIAL_DERIVATIVE_H
