#pragma once
#ifndef EVALUATE_CPU_H
#define EVALUATE_CPU_H
#include "../GP/Evaluator.h"
#include "ProblemHelper.h"
#include "MeshIntersection.h"
#include "BezierCurvature.h"
#include "PeriodicMesh.h"
#include <chrono>

#define INVALID_FITNESS 1e10;

class EvaluateCpu: public Evaluator
{
private:
	std::unique_ptr<ProblemHelper> helper;
	std::unique_ptr<MeshIntersection> intersection;
	std::unique_ptr<BezierCurvature> curvature;

	arma::dcube Gamma2Mesh;
	StarLike3DBoundary Gamma1;

	Collocation boundary_cyclic;
	arma::dcube boundary_cyclic_meshgrid;

	Collocation sources;
	arma::dmat G2Distance;
	
public:
	EvaluateCpu(std::unique_ptr<ProblemHelper> helper, std::unique_ptr<MeshIntersection> inter, std::unique_ptr<BezierCurvature> curv);
	// Inherited via Evaluator
	virtual double evaluateOne(const std::weak_ptr<Individuum> individuum) override;
	virtual void evaluatePopulation(Population& population) override;
};



#endif // !EVALUATE_CPU_H
