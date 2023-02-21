#pragma once
#ifndef PERIODIC_MESH_H
#define PERIODIC_MESH_H
#include <armadillo>
namespace periodic_mesh
{
	extern bool isPeriodic(const arma::dcube& mesh);
}
#endif // !PERIODIC_MESH_H
