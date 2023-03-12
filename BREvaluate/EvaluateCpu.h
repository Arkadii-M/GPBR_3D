#pragma once
#ifndef EVALUATE_CPU_H
#define EVALUATE_CPU_H
#include "../GP/Evaluator.h"
#include "ProblemHelper.h"
#include "MeshIntersection.h"
#include "BezierCurvature.h"
#include "PeriodicMesh.h"
#include "ErrorFunction.h"
#include <chrono>

#define INVALID_FITNESS 1e10;

class EvaluateCpu: public Evaluator
{
private:
	std::shared_ptr<ProblemHelper> helper;
	std::unique_ptr<MeshIntersection> intersection;
	std::unique_ptr<BezierCurvature> curvature;
	std::shared_ptr<ErrorFunction> error;

	//arma::dcube Gamma2Mesh;
	//StarLike3DBoundary Gamma1;

	//Collocation boundary_cyclic;
	//arma::dcube boundary_cyclic_meshgrid;

	//Collocation sources;

	arma::dcube boundary_cyclic_meshgrid;
	std::shared_ptr<ProblemData> data;
	arma::dcolvec f_exact;
	arma::dmat G2Distance;
	
public:
	EvaluateCpu(std::shared_ptr<ProblemHelper> helper, std::shared_ptr<ErrorFunction> err, std::unique_ptr<MeshIntersection> inter, std::unique_ptr<BezierCurvature> curv);
	// Inherited via Evaluator
	virtual double evaluateOne(const std::weak_ptr<Individuum> individuum) override;
	virtual void evaluatePopulation(Population& population) override;
};



#endif // !EVALUATE_CPU_H
