#pragma once
#ifndef STAR_LIKE_3D_BOUNDARY_H
#define STAR_LIKE_3D_BOUNDARY_H
#include <functional>
#include <armadillo>

typedef std::function<double(double, double)> rfunc;
typedef std::function<arma::dmat(arma::dmat, arma::dmat)> rfunc_mat;
typedef std::function<arma::dcolvec(arma::dcolvec, arma::dcolvec)> rfunc_vec;
class StarLike3DBoundary
{
public:
	StarLike3DBoundary();
	arma::dcube operator()(arma::dcolvec r_vals, arma::dcolvec theta, arma::dcolvec phi);
	arma::dcube operator()(arma::dmat r_matrix, arma::dmat theta, arma::dmat phi);
private:
	arma::dcube sphereBase(arma::dcolvec theta, arma::dcolvec phi);
	arma::dcube sphereBase(arma::dmat theta, arma::dmat phi);
};




#endif // STAR_LIKE_3D_BOUNDARY_H