#include "MFSCollocation.h"

MFSCollocation::MFSCollocation(uint n_colocation, uint n_sources)
{
	formLinspaceCollocation(n_colocation, n_colocation);
	formLinspaceSources(n_sources, n_sources);
}

Collocation MFSCollocation::getBoundary() const
{
	return boundary;
}

Collocation MFSCollocation::getSources() const
{
	return sources;
}

Collocation MFSCollocation::getBoundaryCyclic() const
{
	return boundary_cyclyc;
}

Collocation MFSCollocation::getSourcesCyclic() const
{
	return sources_cyclyc;
}

void MFSCollocation::formLinspaceCollocation(uint n_theta, uint n_phi)
{
	arma::dcolvec thethas = arma::linspace(0,arma::datum::pi,n_theta); // thetha in [0,pi]

	arma::dcolvec phis = arma::dcolvec(n_phi); // [0,2*pi)
	arma::dcolvec phis_cycle = arma::dcolvec(n_phi + 1);// [0,2*pi]
	for (uint i = 0; i < n_phi; ++i)
	{
		phis(i) = (2 * arma::datum::pi / (double)n_phi) * (double)i;
	}
	phis_cycle(arma::span(0, n_phi - 1)) = phis;
	phis_cycle(n_phi) = 2 * arma::datum::pi;

	this->boundary = Collocation(thethas, phis);
	this->boundary_cyclyc = Collocation(thethas, phis_cycle);
}

void MFSCollocation::formLinspaceSources(uint n_theta, uint n_phi)
{
	arma::dcolvec thethas = arma::linspace(0, arma::datum::pi, n_theta); // thetha in [0,pi]

	arma::dcolvec phis = arma::dcolvec(n_phi); // [0,2*pi)
	arma::dcolvec phis_cycle = arma::dcolvec(n_phi + 1);// [0,2*pi]
	for (uint i = 0; i < n_phi; ++i)
	{
		phis(i) = (2 * arma::datum::pi / (double)n_phi) * (double)i;
	}
	phis_cycle(arma::span(0, n_phi - 1)) = phis;
	phis_cycle(n_phi) = 2 * arma::datum::pi;

	this->sources = Collocation(thethas, phis);
	this->sources_cyclyc = Collocation(thethas, phis_cycle);
}

