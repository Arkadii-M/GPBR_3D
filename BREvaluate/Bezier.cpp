#include "Bezier.h"

Bezier::Bezier(uint power, arma::drowvec t):
	power(power)
{
	if (power <= 1)
		throw std::invalid_argument("Bezier curve power have to be >= 1");
	fillBase();

	auto t_mat = arma::Mat<double>(t.n_elem, power + 1, arma::fill::ones);
	uint curr_power = power;
	for (int i = 0; i < power; ++i) // Last column has to be ones
	{
		t_mat.col(i) = t.t();
		t_mat.col(i).transform([curr_power](double val) {return pow(val, curr_power); });
		curr_power--;
	}
	TMat = t_mat;
	FixedTBase = t_mat * Base;
}

arma::dmat Bezier::operator()(const arma::dmat& Points)
{
	return FixedTBase * Points;
}

Bezier::uint Bezier::factorial(uint n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

inline arma::Row<double> Bezier::Cj(uint j)
{
	auto res = arma::Row<double>(power + 1);
	double mult = (double)factorial(power) / (double)(factorial(power - j));
	for (uint i = 0; i <= j; ++i)
		res(i) = pow(-1.0, i + j) / (factorial(i) * factorial(j - i));
	return res * mult;

}

void Bezier::fillBase()
{
	Base = arma::dmat(power + 1, power + 1);
	for (int i = power; i >= 0; --i)
	{
		Base.row(power - i) = Cj(i).as_row();
	}
}
