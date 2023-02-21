#pragma once
#include <armadillo>
#ifndef PROBLEM_HELPER_H
#define PROBLEM_HELPER_H

#include "BoundaryCondtition.h"
#include "MFSCollocation.h"
#include "StarlikeBoundary.h"
#include "SphereBoundary.h"

class ProblemHelper
{
	StarLike3DBoundary Gamma1;
	MFS_BC Gamma1Cond;

	SphereBoundary Gamma2;
	MFS_BC Gamma2Cond;
	MFS_BC Gamma2TestCond;

	const MFSCollocation collocation;
	const Collocation boundary_collocation;
	const Collocation sources_collocation;

	const arma::dcube G2boundary;
	const arma::dcube G2sources;


public:
	ProblemHelper(MFSCollocation collocation,
		StarLike3DBoundary Gamma1,
		MFS_BC Gamma1Cond,
		SphereBoundary Gamma2,
		MFS_BC Gamma2Cond);

	void setTestCondition(MFS_BC Gamma2TestCond);
	void setG1Condition(MFS_BC Gamma1Cond);
	void setG2Condition(MFS_BC Gamma2Cond);

	StarLike3DBoundary getGamma1() const;
	SphereBoundary getGamma2() const;



	arma::dmat formMatrix(const arma::dcube& G1_boundary, const arma::dcube& G1_sources);
	arma::dcolvec formColumn(const arma::dcube& G1_boundary);
	arma::dcolvec uApprox(const arma::dcolvec& lambda, const arma::dcube& X, const  arma::dcube& G1_sources);
	double l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources);
	const MFSCollocation getCollocation() const;


	static arma::dcube meshGrid(arma::dcolvec x, arma::dcolvec y);
private:

	arma::dmat module(arma::dcube X, arma::dcube Y);
	arma::dmat phi(arma::dcube X, arma::dcube Y);
	arma::dmat dPhi(arma::dcube X, arma::dcube Y);
	arma::dcube nu();

	arma::dcube formSourcesRepeate(const arma::dcube& G1_sources, const unsigned short n_repeat);


};
#endif // MFS_HELPER_H