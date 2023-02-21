#pragma once
#ifndef BEZIER_H
#define BEZIER_H

#include <armadillo>
class Bezier
{
private:
	using uint = unsigned int;

	const uint power;
	arma::dmat Base;
	arma::dmat TMat;
	arma::dmat FixedTBase;

public:
	Bezier(uint power,arma::drowvec t);
	arma::dmat operator()(const arma::dmat& Points);

private:
	inline uint factorial(uint n);
	inline arma::Row<double> Cj(uint j);
	void fillBase();


};


#endif // BEZIER_TEMPLATE_H