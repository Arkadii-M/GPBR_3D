#pragma once
#ifndef BEZIER_CURVATURE_H
#define BEZIER_CURVATURE_H
#include <armadillo>
#include "Bezier.h"
class BezierCurvature
{
private:
	using uint = unsigned int;
	Bezier d_curve;
	Bezier dd_curve;
	const double threshold;
	const uint curve_power;

public:
	BezierCurvature(uint curve_power, arma::drowvec t, double threshold);

	arma::drowvec curvature(const arma::dmat& points);
	bool curvatureCheck(const arma::dmat& points);
	bool checkMesh(const arma::dcube& mesh);

};

#endif // !BEZIER_CURVATURE_H
