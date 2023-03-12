#include "ProblemData.h"

ProblemData::ProblemData(
	StarLike3DBoundary g1Boundary,
	SphereBoundary g2Boundary,
	MFS_BC g1Cond,
	MFS_BC g2Cond,
	MFSCollocation collocation):
	G1Boundary(g1Boundary),
	G2Boundary(g2Boundary),
	G1Cond(g1Cond),
	G2Cond(g2Cond),
	G2TestCond(nullptr),
	collocation(collocation)
{
	G2BoundaryValues = G2Boundary(getBoundaryTheta(), getBoundaryPhi());
	G2SourcesValues = G2Boundary(getSourcesTheta(), getSourcesPhi());
}

StarLike3DBoundary ProblemData::getG1Boundary()
{
	return G1Boundary;
}

SphereBoundary ProblemData::getG2Boundary()
{
	return G2Boundary;
}

MFS_BC ProblemData::getG1Condition()
{
	return G1Cond;
}

MFS_BC ProblemData::getG2Condition()
{
	return G2Cond;
}

MFS_BC ProblemData::getG2TestCondition()
{
	return G2TestCond;
}

void ProblemData::setG2TestCondition(MFS_BC g2Cond)
{
	G2TestCond = g2Cond;
	G2TestCondValues = G2TestCond(G2BoundaryValues);
}

MFSCollocation ProblemData::getCollocation()
{
	return collocation;
}

Collocation ProblemData::getBoundaryCollocation() const
{
	return collocation.getBoundary();
}

arma::dcolvec ProblemData::getBoundaryTheta() const
{
	return collocation.getBoundary().getThetha();
}

arma::dcolvec ProblemData::getBoundaryPhi() const
{
	return collocation.getBoundary().getPhi();
}

ProblemData::uint ProblemData::getNBoundary() const
{
	return collocation.getBoundary().getN();
}

Collocation ProblemData::getSourcesCollocation() const
{
	return collocation.getSources();
}

arma::dcolvec ProblemData::getSourcesTheta() const
{
	return collocation.getSources().getThetha();
}

arma::dcolvec ProblemData::getSourcesPhi() const
{
	return collocation.getSources().getPhi();
}

ProblemData::uint ProblemData::getNSources() const
{
	return collocation.getSources().getN();
}

arma::dcube ProblemData::getG2BondaryValues()
{
	return G2BoundaryValues;
}

arma::dcube ProblemData::getG2SourcesValues()
{
	return G2SourcesValues;
}

arma::dcolvec ProblemData::getG2TestConditionValues()
{
	return G2TestCondValues;
}