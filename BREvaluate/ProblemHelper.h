#pragma once
#include <armadillo>
#ifndef PROBLEM_HELPER_H
#define PROBLEM_HELPER_H

#include "BoundaryCondtition.h"
#include "MFSCollocation.h"
#include "StarlikeBoundary.h"
#include "SphereBoundary.h"
#include "ProblemData.h"

class ProblemHelper
{
public:
	using uint = unsigned int;
private:
	std::shared_ptr<ProblemData> data;


public:
	ProblemHelper(std::shared_ptr<ProblemData> data);
	std::shared_ptr<ProblemData> getProblemData();

	arma::dmat formMatrix(const arma::dcube& G1_boundary, const arma::dcube& G1_sources);
	arma::dcolvec formColumn(const arma::dcube& G1_boundary);
	arma::dcolvec uApprox(const arma::dcolvec& lambda, const arma::dcube& X, const  arma::dcube& G1_sources);
	arma::dcube partialU(const arma::dcolvec& lambda, const arma::dcube& X, const arma::dcube& dX, const  arma::dcube& G1_sources);
	bool uOnG2(const arma::dcube& G1_boundary, const arma::dcube& G1_sources, arma::dcolvec& res);


	//double l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources);
	//bool l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources,double & res);

	static arma::dcube meshGrid(arma::dcolvec x, arma::dcolvec y);
private:

	arma::dmat module(arma::dcube X, arma::dcube Y);
	arma::dmat phi(arma::dcube X, arma::dcube Y);
	arma::dmat dPhi(arma::dcube X, arma::dcube Y);
	arma::dcube nu();

	arma::dcube formSourcesRepeate(const arma::dcube& G1_sources, const unsigned short n_repeat);


};
#endif // MFS_HELPER_H