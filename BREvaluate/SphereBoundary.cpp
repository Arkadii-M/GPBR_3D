#include "SphereBoundary.h"

SphereBoundary::SphereBoundary(double radius):
	radius(radius)
{
}

arma::dcube SphereBoundary::operator()(arma::dcolvec theta, arma::dcolvec phi)
{
	auto base = sphereBase(theta, phi);
	base.slice(0) *= radius; //TODO: check if multiply right
	base.slice(1) *= radius;
	base.slice(2) *= radius;

	return base;
}

arma::dcube SphereBoundary::operator()(arma::dmat theta, arma::dmat phi)
{
	auto base = sphereBase(theta, phi);
	base.slice(0) *= radius; //TODO: check if multiply right
	base.slice(1) *= radius;
	base.slice(2) *= radius;

	return base;
}

arma::dcube SphereBoundary::sphereBase(arma::dcolvec theta, arma::dcolvec phi)
{
	auto res = arma::dcube(theta.n_elem, 1, 3); // x,y,z matrices

	arma::dcolvec sin_theta = sin(theta);

	res.slice(0) = sin_theta % cos(phi); // Element-wise multiplication
	res.slice(1) = sin_theta % sin(phi);
	res.slice(2) = cos(theta);
	return res;
}

arma::dcube SphereBoundary::sphereBase(arma::dmat theta, arma::dmat phi)
{
	auto res = arma::dcube(theta.n_rows, theta.n_cols, 3); // x,y,z matrices

	arma::dmat sin_theta = sin(theta);

	res.slice(0) = sin_theta % cos(phi); // Element-wise multiplication
	res.slice(1) = sin_theta % sin(phi);
	res.slice(2) = cos(theta);
	return res;
}
