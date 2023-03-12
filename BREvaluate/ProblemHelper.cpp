#include "ProblemHelper.h"

ProblemHelper::ProblemHelper(std::shared_ptr<ProblemData> data) :
	data(data)
{
}

std::shared_ptr<ProblemData> ProblemHelper::getProblemData()
{
	return data;
}

arma::Mat<double> ProblemHelper::formMatrix(const arma::dcube& G1_boundary, const arma::dcube& G1_sources)
{
	uint n_collocation = data->getNBoundary();
	uint n_sources = data->getNSources();

	arma::Mat<double> res = arma::Mat<double>(2 * n_collocation, n_sources, arma::fill::ones);

	arma::dcube G1repeat = arma::dcube(n_collocation, n_sources, 3);
	arma::dcube G2repeat = arma::dcube(n_collocation, n_sources, 3);

	G1repeat.slice(0) = arma::repmat(G1_boundary.slice(0), 1, n_sources);
	G1repeat.slice(1) = arma::repmat(G1_boundary.slice(1), 1, n_sources);
	G1repeat.slice(2) = arma::repmat(G1_boundary.slice(2), 1, n_sources);

	auto G2boundaryValues = data->getG2BondaryValues();
	G2repeat.slice(0) = arma::repmat(G2boundaryValues.slice(0), 1, n_sources);
	G2repeat.slice(1) = arma::repmat(G2boundaryValues.slice(1), 1, n_sources);
	G2repeat.slice(2) = arma::repmat(G2boundaryValues.slice(2), 1, n_sources);


	arma::dcube Sources_repeat = this->formSourcesRepeate(G1_sources, n_collocation);
	/*
	*	Phi(x1_1,y1) ... Phi(x1_1,y_n)
	*		.				.
	*		.				.
	*		.				.
	*	Phi(x1_n,y_1)		Phi(x1_n,y_n)
	*	DPhi(x2_1,y_1) ... DPhi(x2_1,y_n)
	*		.				.
	*		.				.
	*		.				.
	*	DPhi(x2_n,y_1)		DPhi(x2_n,y_n)
	*/


	res.submat(arma::span(0, n_collocation - 1), arma::span(0, n_sources - 1)) = phi(G1repeat, Sources_repeat);
	res.submat(arma::span(n_collocation, 2 * n_collocation - 1), arma::span(0, n_sources - 1)) = dPhi(G2repeat, Sources_repeat);


	return res;
}

arma::dcolvec ProblemHelper::formColumn(const arma::dcube& G1_boundary)
{
	
	uint n_collocation = data->getNBoundary();

	arma::dcolvec res = arma::dcolvec(2 * n_collocation);
	res.subvec(0, n_collocation - 1) = data->getG1Condition()(G1_boundary);
	res.subvec(n_collocation, 2 * n_collocation - 1) = data->getG2Condition()(data->getG2BondaryValues());

	return res;
}

arma::Mat<double> ProblemHelper::module(arma::dcube X, arma::dcube Y)
{
	/*
	* Each (X,Y) is cube matrices. They have three slices ( x,y,z) coordinates
	*/

	//tex:
	//$X-Y$ cordinate difference
	//$(X-Y)^2$ is element wise power 
	// $\sum(X-Y)^2$ gives us a matrix. It sums throw slices
	// $\sqrt{\sum(X-Y)^2}$ next just take square root of each element

	return 	sqrt(sum(pow((X - Y), 2), 2));
}

arma::Mat<double> ProblemHelper::phi(arma::dcube X, arma::dcube Y)
{
	return 1 / (4 * arma::datum::pi * module(X, Y));
}

arma::Mat<double>  ProblemHelper::dPhi(arma::dcube X, arma::dcube Y)
{
	//arma::dcube nu = this->nu(); //TODO: implement
	//arma::Mat<double> en = sum((X - Y) % this->nu(), 2);// dot analog for cube matrices
	//arma::Mat<double> den = 4 * arma::datum::pi * pow(module(X, Y), 3);

	//return -en / den;
	arma::Mat<double> en = sum((X - Y) % this->nu(), 2);// dot analog for cube matrices
	arma::Mat<double> den = 4 * arma::datum::pi * pow(module(X, Y), 3);
	return -en / den;
}

arma::dcube ProblemHelper::nu()
{
	auto thetha = data->getBoundaryTheta();
	auto phi = data->getBoundaryPhi();
	auto sin_thetha = sin(thetha);
	auto den = 1 / abs(sin_thetha);
	auto X = (pow(sin_thetha, 2) % cos(phi)) / den;
	auto Y = (pow(sin_thetha, 2) % sin(phi)) / den;
	auto Z = (sin_thetha % cos(thetha)) / den;

	const uint n_collocation = data->getNBoundary();
	const uint n_sources = data->getNSources();

	arma::dcube Nu_repeate = arma::dcube(n_collocation, n_sources, 3);

	Nu_repeate.slice(0) = arma::repmat(X, 1, n_sources);
	Nu_repeate.slice(1) = arma::repmat(Y, 1, n_sources);
	Nu_repeate.slice(2) = arma::repmat(Z, 1, n_sources);

	return Nu_repeate;
}

arma::dcube ProblemHelper::formSourcesRepeate(const arma::dcube& G1_sources, const unsigned short n_repeat)
{
	uint n_sources = data->getNSources();

	auto G2_vals = data->getG2SourcesValues();

	arma::dcube Sources_repeat = arma::dcube(n_repeat, n_sources, 3);

	arma::uvec indeces = arma::regspace<arma::uvec>(0, 1, n_sources - 1);
	arma::uvec even_indices = arma::regspace<arma::uvec>(0, 2, n_sources - 1);
	arma::uvec odd_indices = arma::regspace<arma::uvec>(1, 2, n_sources - 1);

	// Modify G1 and G2
	auto G1_sources_copy = G1_sources;

	G1_sources_copy.each_slice([&, odd_indices](arma::mat& X) { X.rows(odd_indices).zeros(); });
	G1_sources_copy *= 0.5;

	G2_vals.each_slice([&, even_indices](arma::mat& X) { X.rows(even_indices).zeros(); });
	G2_vals *= 2;

	arma::dcube Sources_values = G1_sources_copy + G2_vals;

	Sources_repeat.slice(0) = arma::repmat(Sources_values.slice(0).t(), n_repeat, 1);
	Sources_repeat.slice(1) = arma::repmat(Sources_values.slice(1).t(), n_repeat, 1);
	Sources_repeat.slice(2) = arma::repmat(Sources_values.slice(2).t(), n_repeat, 1);

	return Sources_repeat;
}


arma::dcolvec ProblemHelper::uApprox(const arma::dcolvec& lambda, const arma::dcube& X, const  arma::dcube& G1_sources)
{
	int n_x = X.n_rows;
	uint n_sources = data->getNSources();
	arma::dcube Xrepeat = arma::dcube(n_x, n_sources, 3);
	Xrepeat.slice(0) = arma::repmat(X.slice(0), 1, n_sources);
	Xrepeat.slice(1) = arma::repmat(X.slice(1), 1, n_sources);
	Xrepeat.slice(2) = arma::repmat(X.slice(2), 1, n_sources);


	arma::dcube Sources_repeat = this->formSourcesRepeate(G1_sources, n_x);


	arma::Mat<double> Phi = phi(Xrepeat, Sources_repeat);
	return Phi * lambda;
}

arma::dcube ProblemHelper::partialU(const arma::dcolvec& lambda, const arma::dcube& X, const arma::dcube& dX, const  arma::dcube& G1_sources)
{
	// There is a partial derivative: du/(dx(t)) * dx/dt
	// dX is a cube of user provided derivatives
	int n_x = X.n_rows;
	uint n_sources = data->getNSources();
	arma::dcube Xrepeat = arma::dcube(n_x, n_sources, 3);
	Xrepeat.slice(0) = arma::repmat(X.slice(0), 1, n_sources);
	Xrepeat.slice(1) = arma::repmat(X.slice(1), 1, n_sources);
	Xrepeat.slice(2) = arma::repmat(X.slice(2), 1, n_sources);


	arma::dcube Sources_repeat = this->formSourcesRepeate(G1_sources, n_x);


	arma::Mat<double> d_Phi = dPhi(Xrepeat, Sources_repeat);
	return (d_Phi* lambda)% dX.each_slice();
}
bool ProblemHelper::uOnG2(const arma::dcube& G1_boundary, const arma::dcube& G1_sources, arma::dcolvec& res)
{
	arma::dcolvec lambda;
	bool status = arma::solve(lambda, formMatrix(G1_boundary, G1_sources), formColumn(G1_boundary), arma::solve_opts::no_approx);
	if (!status)
		return false;

	auto G2boundary = data->getG2BondaryValues();
	res = uApprox(lambda, G2boundary, G1_sources);

	return true;
}

//double ProblemHelper::l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources)
//{
//	auto A = formMatrix(G1_boundary, G1_sources);
//	auto B = formColumn(G1_boundary);
//
//	arma::dcolvec lambda = arma::solve(A,B, arma::solve_opts::no_approx);
//
//	auto G2boundary = data->getG2BondaryValues();
//	arma::dcolvec u = uApprox(lambda, G2boundary, G1_sources);
//
//	arma::dcolvec f_vals = data->getG2TestConditionValues();
//
//	return sqrt(sum(pow(u - f_vals, 2)));
//}
//
//bool ProblemHelper::l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources, double& res)
//{
//
//	arma::dcolvec lambda;
//	bool status = arma::solve(lambda,formMatrix(G1_boundary, G1_sources), formColumn(G1_boundary), arma::solve_opts::no_approx);
//	if (!status)
//		return false;
//
//	auto G2boundary = data->getG2BondaryValues();
//	arma::dcolvec u = uApprox(lambda, G2boundary, G1_sources);
//
//	arma::dcolvec f_vals = data->getG2TestConditionValues();
//
//	res= sqrt(sum(pow(u - f_vals, 2)));
//	return true;
//}

arma::dcube ProblemHelper::meshGrid(arma::dcolvec x, arma::dcolvec y)
{
	int len_x = x.n_elem;
	int len_y = y.n_elem;

	auto res = arma::Cube<double>(len_y, len_x, 2);

	res.slice(0) = arma::repmat(x.t(), len_y, 1);
	res.slice(1) = arma::repmat(y, 1, len_x);

	return res;
}

