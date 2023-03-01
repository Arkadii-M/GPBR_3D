#include "ProblemHelper.h"

ProblemHelper::ProblemHelper(
	MFSCollocation collocation,
	StarLike3DBoundary Gamma1,
	MFS_BC Gamma1Cond,
	SphereBoundary Gamma2,
	MFS_BC Gamma2Cond) :
	collocation(collocation),
	boundary_collocation(collocation.getBoundary()),
	sources_collocation(collocation.getSources()),
	Gamma1(Gamma1),
	Gamma1Cond(Gamma1Cond),
	Gamma2(Gamma2),
	Gamma2Cond(Gamma2Cond),
	Gamma2TestCond(NULL),
	G2boundary(Gamma2(boundary_collocation.getThetha(), boundary_collocation.getPhi())),
	G2sources(Gamma2(sources_collocation.getThetha(), sources_collocation.getPhi()))
{
}

void ProblemHelper::setTestCondition(MFS_BC Gamma2TestCond)
{
	this->Gamma2TestCond = Gamma2TestCond;
}

void ProblemHelper::setG1Condition(MFS_BC Gamma1Cond)
{
	this->Gamma1Cond = Gamma1Cond;
}

void ProblemHelper::setG2Condition(MFS_BC Gamma2Cond)
{
	this->Gamma2Cond = Gamma2Cond;
}

StarLike3DBoundary ProblemHelper::getGamma1() const
{
	return Gamma1;
}

SphereBoundary ProblemHelper::getGamma2() const
{
	return Gamma2;
}

arma::Mat<double> ProblemHelper::formMatrix(const arma::dcube& G1_boundary, const arma::dcube& G1_sources)
{
	int n_collocation = boundary_collocation.getN();
	int n_sources = sources_collocation.getN();

	arma::Mat<double> res = arma::Mat<double>(2 * n_collocation, n_sources, arma::fill::ones);

	arma::dcube G1repeat = arma::dcube(n_collocation, n_sources, 3);
	arma::dcube G2repeat = arma::dcube(n_collocation, n_sources, 3);

	G1repeat.slice(0) = arma::repmat(G1_boundary.slice(0), 1, n_sources);
	G1repeat.slice(1) = arma::repmat(G1_boundary.slice(1), 1, n_sources);
	G1repeat.slice(2) = arma::repmat(G1_boundary.slice(2), 1, n_sources);

	//auto G2_vals = Gamma2(coll_thetha, coll_phi);
	//auto G2_vals = G2boundary;
	G2repeat.slice(0) = arma::repmat(G2boundary.slice(0), 1, n_sources);
	G2repeat.slice(1) = arma::repmat(G2boundary.slice(1), 1, n_sources);
	G2repeat.slice(2) = arma::repmat(G2boundary.slice(2), 1, n_sources);


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
	int n_collocation = boundary_collocation.getN();

	arma::dcolvec res = arma::dcolvec(2 * n_collocation);
	res.subvec(0, n_collocation - 1) = Gamma1Cond(G1_boundary);
	res.subvec(n_collocation, 2 * n_collocation - 1) = Gamma2Cond(G2boundary);

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
	auto thetha = boundary_collocation.getThetha();
	auto phi = boundary_collocation.getPhi();
	auto sin_thetha = sin(thetha);
	auto den = 1 / abs(sin_thetha);
	auto X = (pow(sin_thetha, 2) % cos(phi)) / den;
	auto Y = (pow(sin_thetha, 2) % sin(phi)) / den;
	auto Z = (sin_thetha % cos(thetha)) / den;

	const int n_collocation = boundary_collocation.getN();
	const int n_sources = sources_collocation.getN();

	arma::dcube Nu_repeate = arma::dcube(n_collocation, n_sources, 3);

	Nu_repeate.slice(0) = arma::repmat(X, 1, n_sources);
	Nu_repeate.slice(1) = arma::repmat(Y, 1, n_sources);
	Nu_repeate.slice(2) = arma::repmat(Z, 1, n_sources);

	return Nu_repeate;
}

arma::dcube ProblemHelper::formSourcesRepeate(const arma::dcube& G1_sources, const unsigned short n_repeat)
{
	//int n_collocation = boundary_collocation.getN();
	int n_sources = sources_collocation.getN();

	//auto G2_vals = Gamma2(sources_thetha, sources_phi);
	auto G2_vals = G2sources;

	//arma::dcube Sources_repeat = arma::dcube(n_collocation, n_sources, 3);
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
	int n_sources = sources_collocation.getN();
	arma::dcube Xrepeat = arma::dcube(n_x, n_sources, 3);
	Xrepeat.slice(0) = arma::repmat(X.slice(0), 1, n_sources);
	Xrepeat.slice(1) = arma::repmat(X.slice(1), 1, n_sources);
	Xrepeat.slice(2) = arma::repmat(X.slice(2), 1, n_sources);


	arma::dcube Sources_repeat = this->formSourcesRepeate(G1_sources, n_x);


	arma::Mat<double> Phi = phi(Xrepeat, Sources_repeat);
	return Phi * lambda;
}

double ProblemHelper::l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources)
{
	//arma::dcolvec lambda = arma::solve(formMatrix(G1_boundary, G1_sources), formColumn(G1_boundary), arma::solve_opts::force_approx);
	auto A = formMatrix(G1_boundary, G1_sources);
	auto B = formColumn(G1_boundary);
	double cond_A = arma::cond(A);
	//arma::dcolvec lambda = arma::solve(A.t()*A, A.t() * B, arma::solve_opts::force_approx);
	arma::dcolvec lambda = arma::solve(A,B, arma::solve_opts::no_approx);

	int n_collocation = boundary_collocation.getN();

	//auto coll_thetha = boundary_collocation.getThetha();
	//auto coll_phi = boundary_collocation.getPhi();

	//auto G2_vals = Gamma2(coll_thetha, coll_phi);
	//auto G2_vals = G2boundary;

	arma::dcolvec u = uApprox(lambda, G2boundary, G1_sources);

	arma::dcolvec f_vals = Gamma2TestCond(G2boundary);

	return sqrt(sum(pow(u - f_vals, 2)));
}

bool ProblemHelper::l2Norm(const arma::dcube& G1_boundary, const arma::dcube& G1_sources, double& res)
{

	arma::dcolvec lambda;
	//auto A = formMatrix(G1_boundary, G1_sources);
	//if (arma::cond(A) > 10e2)
	//{
	//	return false;
	//}
	bool status = arma::solve(lambda,formMatrix(G1_boundary, G1_sources), formColumn(G1_boundary), arma::solve_opts::no_approx);
	if (!status)
		return false;

	//auto A = formMatrix(G1_boundary, G1_sources);
	//auto B = formColumn(G1_boundary);
	//arma::dcolvec lambda = arma::solve(A.t() * A, A.t() * B, arma::solve_opts::force_approx);

	int n_collocation = boundary_collocation.getN();

	//auto coll_thetha = boundary_collocation.getThetha();
	//auto coll_phi = boundary_collocation.getPhi();

	//auto G2_vals = Gamma2(coll_thetha, coll_phi);
	//auto G2_vals = G2boundary;

	arma::dcolvec u = uApprox(lambda, G2boundary, G1_sources);

	arma::dcolvec f_vals = Gamma2TestCond(G2boundary);

	res= sqrt(sum(pow(u - f_vals, 2)));
	return true;
}

const MFSCollocation ProblemHelper::getCollocation() const
{
	return collocation;
}

arma::dcube ProblemHelper::meshGrid(arma::dcolvec x, arma::dcolvec y)
{
	int len_x = x.n_elem;
	int len_y = y.n_elem;

	auto res = arma::Cube<double>(len_y, len_x, 2);

	res.slice(0) = arma::repmat(x.t(), len_y, 1);
	res.slice(1) = arma::repmat(y, 1, len_x);

	return res;
}

