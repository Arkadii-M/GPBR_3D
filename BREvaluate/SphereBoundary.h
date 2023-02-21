#pragma once
#ifndef SPHERE_BOUNDARY_H
#define SPHERE_BOUNDARY_H
#include <functional>
#include <armadillo>
typedef std::function<double(double, double)> rfunc;
typedef std::function<arma::dmat(arma::dmat, arma::dmat)> rfunc_mat;
class SphereBoundary
{
private:
	double radius;
public:
	SphereBoundary(double radius);
	arma::dcube operator()(arma::dcolvec theta, arma::dcolvec phi);
	arma::dcube operator()(arma::dmat theta, arma::dmat phi);
private:
	arma::dcube sphereBase(arma::dcolvec theta, arma::dcolvec phi);
	arma::dcube sphereBase(arma::dmat theta, arma::dmat phi);
};




#endif // SPHERE_BOUNDARY_H