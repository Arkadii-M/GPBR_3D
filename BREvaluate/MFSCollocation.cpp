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
	arma::dcolvec thethas = arma::dcolvec(n_theta);
	arma::dcolvec thethas_cycle = arma::dcolvec(n_theta + 1);
	for (uint i = 0; i < n_theta; ++i)
	{
		thethas(i) = (arma::datum::pi / (double)n_theta) * (double)i;
	}
	thethas_cycle(arma::span(0, n_theta - 1)) = thethas;
	thethas_cycle(n_theta) = arma::datum::pi;


	arma::dcolvec phis = arma::dcolvec(n_phi);
	arma::dcolvec phis_cycle = arma::dcolvec(n_phi + 1);
	for (uint i = 0; i < n_phi; ++i)
	{
		phis(i) = (2 * arma::datum::pi / (double)n_phi) * (double)i;
	}
	phis_cycle(arma::span(0, n_phi - 1)) = phis;
	phis_cycle(n_phi) = 2 * arma::datum::pi;

	this->boundary = Collocation(thethas, phis);

	this->boundary_cyclyc = Collocation(thethas_cycle, phis_cycle);
}

void MFSCollocation::formLinspaceSources(uint n_theta, uint n_phi)
{
	arma::dcolvec thethas = arma::dcolvec(n_theta);
	arma::dcolvec thethas_cycle = arma::dcolvec(n_theta + 1);
	for (uint i = 0; i < n_theta; ++i)
	{
		thethas(i) = (arma::datum::pi / (double)n_theta) * (double)i;
	}
	thethas_cycle(arma::span(0, n_theta - 1)) = thethas;
	thethas_cycle(n_theta) = arma::datum::pi;


	arma::dcolvec phis = arma::dcolvec(n_phi);
	arma::dcolvec phis_cycle = arma::dcolvec(n_phi + 1);
	for (uint i = 0; i < n_phi; ++i)
	{
		phis(i) = (2 * arma::datum::pi / (double)n_phi) * (double)i;
	}
	phis_cycle(arma::span(0, n_phi - 1)) = phis;
	phis_cycle(n_phi) = 2 * arma::datum::pi;

	this->sources = Collocation(thethas, phis);

	this->sources_cyclyc = Collocation(thethas_cycle, phis_cycle);
}

