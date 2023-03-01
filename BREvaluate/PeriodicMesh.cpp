#include "PeriodicMesh.h"
namespace periodic_mesh
{
	bool periodic_mesh::isPeriodic(const arma::dcube& mesh)
	{
		// first check for phi period
		bool ok = true;
		mesh.each_slice([&](const arma::dmat& mat) {
			ok &= arma::approx_equal(mat.row(0), mat.row(mat.n_rows - 1), "absdiff", 1e-5); // check for phi period
			// check poles
			auto& first_col = mat.col(0);
			ok &= arma::all(abs(first_col - first_col(0)) < 1e-5);

			auto& last_col = mat.col(mat.n_cols - 1);
			ok &= arma::all(abs(last_col - last_col(0)) < 1e-5);
			});
		return ok;
	}
}