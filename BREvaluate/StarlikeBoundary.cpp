#include "StarlikeBoundary.h"

StarLike3DBoundary::StarLike3DBoundary()
{
}

arma::dcube StarLike3DBoundary::operator()(arma::dcolvec r_vals, arma::dcolvec theta, arma::dcolvec phi)
{
	if (theta.n_elem != phi.n_elem)
		throw std::invalid_argument(std::format("Input sizes missmatch ({}) and ({})", theta.n_elem, phi.n_elem));
	auto base = sphereBase(theta, phi);

	base.slice(0) %= r_vals;
	base.slice(1) %= r_vals;
	base.slice(2) %= r_vals;

	return base;
}

arma::dcube StarLike3DBoundary::operator()(arma::dmat r_matrix, arma::dmat theta, arma::dmat phi)
{
	if (theta.n_elem != phi.n_elem)
		throw std::invalid_argument(std::format("Input sizes missmatch ({}) and ({})", theta.n_elem, phi.n_elem));
	auto base = sphereBase(theta, phi);

	base.slice(0) %= r_matrix;
	base.slice(1) %= r_matrix;
	base.slice(2) %= r_matrix;

	return base;
}

arma::dcube StarLike3DBoundary::sphereBase(arma::dcolvec theta, arma::dcolvec phi)
{
	auto res = arma::dcube(theta.n_elem, 1, 3); // x,y,z matrices

	arma::dcolvec sin_theta = sin(theta);

	res.slice(0) = sin_theta % cos(phi); // Element-wise multiplication
	res.slice(1) = sin_theta % sin(phi);
	res.slice(2) = cos(theta);
	return res;
}

arma::dcube StarLike3DBoundary::sphereBase(arma::dmat theta, arma::dmat phi)
{
	if (theta.n_rows != phi.n_rows || theta.n_cols != phi.n_cols)
		throw std::invalid_argument(
			std::format("Mesh input sizes missmatch ({}x{}) and ({}x{})",
				theta.n_rows, theta.n_cols,
				phi.n_rows, phi.n_cols));

	//auto res = arma::dmat(theta.n_rows,theta.n_cols);
	auto res = arma::dcube(theta.n_rows, theta.n_cols, 3); // x,y,z matrices

	arma::dmat sin_theta = sin(theta);

	res.slice(0) = sin_theta % cos(phi); // Element-wise multiplication
	res.slice(1) = sin_theta % sin(phi);
	res.slice(2) = cos(theta);

	return res;
}


