#include "BoundaryCondtition.h"

MFS_BC::MFS_BC(bc_func func):
    func(func)
{
}

arma::dcolvec MFS_BC::operator()(arma::dcube X)
{
    return func(X);
}
