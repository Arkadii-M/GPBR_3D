#pragma once
#ifndef MFS_COLLOCATION_H
#define MFS_COLLOCATION_H
#include <armadillo>


class Collocation {
	using uint = unsigned int;
private:
	uint n_elem;
	arma::dcolvec thetha;
	arma::dcolvec phi;

public:
	Collocation() :n_elem(0) {};
	Collocation(arma::dcolvec thetha, arma::dcolvec phi) :
		n_elem(thetha.n_elem),
		thetha(thetha),
		phi(phi)
	{}
	uint getN() const { return n_elem; }
	arma::dcolvec getThetha() const { return thetha; }
	arma::dcolvec getPhi() const { return phi; }

};

class MFSCollocation
{
	using uint = unsigned int;

	uint n;
	Collocation boundary;
	Collocation sources;
	Collocation boundary_cyclyc;
	Collocation sources_cyclyc;


public:
	//MFSCollocation(int n);
	MFSCollocation(uint n_colocation, uint n_sources);

	Collocation getBoundary() const;
	Collocation getSources() const;

	Collocation getBoundaryCyclic() const;
	Collocation getSourcesCyclic() const;


private:
	void formLinspaceCollocation(uint n_theta, uint n_phi);
	void formLinspaceSources(uint n_theta, uint n_phi);

};


#endif // !MFS_COLLOCATION_H
