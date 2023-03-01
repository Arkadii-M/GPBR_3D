#include "PartialTreeDerivative.h"

TreeDerivativeInfo::TreeDerivativeInfo(std::vector<uint> ids):
	diff_ids(ids)
{
}

bool TreeDerivativeInfo::inDiffIdArray(const uint id) const
{
	return std::find(diff_ids.begin(), diff_ids.end(), id) != diff_ids.end();
}

uint TreeDerivativeInfo::getNelements() const
{
	return diff_ids.size();
}


TreeDerivative::TreeDerivative(arma::dmat& x, arma::dcube& dx):
	x(x),
	dx(dx)
{
}

const arma::dmat& TreeDerivative::getElement() const
{
	return x;
}

const arma::dcube& TreeDerivative::getDerivative() const
{
	return dx;
}
