#pragma once
#ifndef BOUNDARY_CONDITION_H
#define BOUNDARY_CONDITION_H
#include <functional>
#include <armadillo>
typedef std::function<arma::dcolvec(arma::dcube)> bc_func;
class MFS_BC {
	bc_func func;
public:
	MFS_BC(bc_func func);
	arma::dcolvec operator()(arma::dcube X);
};
#endif // BOUNDARY_CONDITION_H