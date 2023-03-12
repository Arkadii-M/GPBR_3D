#pragma once
#include "StarlikeBoundary.h"
#include "SphereBoundary.h"
#include "BoundaryCondtition.h"
#include "MFSCollocation.h"
#ifndef PROBLEM_DATA_H
#define PROBLEM_DATA_H
class ProblemData
{
public:
	using uint = unsigned int;
private:
	// Boundary representation
	StarLike3DBoundary G1Boundary;
	SphereBoundary G2Boundary;

	// Boundary condition
	MFS_BC G1Cond;
	MFS_BC G2Cond;
	MFS_BC G2TestCond;

	// Collocation
	MFSCollocation collocation;


	// Precalculated values
	arma::dcube G2BoundaryValues;
	arma::dcube G2SourcesValues;
	arma::dcolvec G2TestCondValues;
public:
	ProblemData(StarLike3DBoundary g1Boundary, SphereBoundary g2Boundary, MFS_BC g1Cond, MFS_BC g2Cond, MFSCollocation collocation);

	StarLike3DBoundary getG1Boundary();
	SphereBoundary getG2Boundary();

	MFS_BC getG1Condition();
	MFS_BC getG2Condition();
	MFS_BC getG2TestCondition();
	void setG2TestCondition(MFS_BC g2Cond);

	MFSCollocation getCollocation();

	Collocation getBoundaryCollocation() const;
	arma::dcolvec getBoundaryTheta() const;
	arma::dcolvec getBoundaryPhi() const;
	uint getNBoundary() const; // return number of boundary collocation

	Collocation getSourcesCollocation() const;
	arma::dcolvec getSourcesTheta() const;
	arma::dcolvec getSourcesPhi() const;
	uint getNSources() const;// return number of sources collocation

	arma::dcube getG2BondaryValues();
	arma::dcube getG2SourcesValues();
	arma::dcolvec getG2TestConditionValues();
};

#endif // !PROBLEM_DATA_H
