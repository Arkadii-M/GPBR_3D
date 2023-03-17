#include "PartialTreeDerivative.h"
//
//TreeDerivativeInfo::TreeDerivativeInfo(std::vector<uint> ids):
//	diff_ids(ids)
//{
//}
//
//bool TreeDerivativeInfo::inDiffIdArray(const uint id) const
//{
//	return std::find(diff_ids.begin(), diff_ids.end(), id) != diff_ids.end();
//}
//
//uint TreeDerivativeInfo::getNelements() const
//{
//	return diff_ids.size();
//}
//
//
//TreeDerivative::TreeDerivative(arma::dmat& x, arma::dcube& dx):
//	x(x),
//	dx(dx)
//{
//}
//
//const arma::dmat& TreeDerivative::getValues() const
//{
//	return x;
//}
//
//const arma::dcube& TreeDerivative::getDerivatives() const
//{
//	return dx;
//}

TreeDerivative::TreeDerivative(arma::dmat vals):
	values(vals)
{
}

TreeDerivative::TreeDerivative(arma::dmat vals, LeafDerivative derivative):
	values(vals)
{
	derivatives.push_back(derivative);
}

void TreeDerivative::setValues(arma::dmat vals)
{
	values = vals;
}

arma::dmat TreeDerivative::getValues() const
{
	return values;
}

std::vector<TreeDerivative::LeafDerivative> TreeDerivative::getDerivatives() const
{
	return derivatives;
}

void TreeDerivative::ConcatDerivatives(TreeDerivative& first, TreeDerivative& second)
{
	//TODO concat derivatives
}

TreeDerivative::LeafDerivative::LeafDerivative(uint id, arma::dmat dx):
	id(id),
	dx(dx)
{
}

uint TreeDerivative::LeafDerivative::getId() const
{
	return id;
}

arma::dmat TreeDerivative::LeafDerivative::getDerivative() const
{
	return dx;
}

arma::dmat TreeDerivative::LeafDerivative::getOtherDerivative() const
{
	return dNotx;
}

void TreeDerivative::LeafDerivative::setDerivative(arma::dmat& dx)
{
	this->dx = dx;
}

void TreeDerivative::LeafDerivative::setOtherDerivative(arma::dmat& dNotx)
{
	this->dNotx = dNotx;
}