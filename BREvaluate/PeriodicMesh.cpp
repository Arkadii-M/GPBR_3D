#include "PeriodicMesh.h"
namespace periodic_mesh
{
	bool periodic_mesh::isPeriodic(const arma::dcube& mesh)
	{
		// first check for phi period
		bool ok = true;

		mesh.each_slice([&](const arma::dmat& mat) {

			ok &= arma::approx_equal(mat.row(0), mat.row(mat.n_rows - 1), "absdiff", 10e-5); // check for phi period
			// check poles TODO: check
			ok &= abs(arma::sum(mat.col(0)) / mat.n_cols - mat.col(0)(0)) < 10e-5;
			ok &= abs(arma::sum(mat.col(mat.n_cols-1)) / mat.n_cols - mat.col(mat.n_cols-1)(0)) < 10e-5;
			});
		return ok;
	}
}