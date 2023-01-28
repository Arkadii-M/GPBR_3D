#pragma once
#ifndef INDIVIDUUM_H
#define INDIVIDUUM_H

#include "ExpressionTree.h"

class Individuum
{
private:
	std::unique_ptr<ExpressionTree> tree;
	double fitness;
	bool is_calculated;

public:
	Individuum(std::unique_ptr<ExpressionTree> tree);
	Individuum(const Individuum& rhs);

	double getFintness() const;
	void setFitness(double fit);

	bool isCalculated() const;
	void setCalculated(bool calc);

	std::unique_ptr<ExpressionTree>& getTree();
	void setTree(std::unique_ptr<ExpressionTree> tree);


	// TODO: add comapare and accumulate for STL.
	static bool cmp_weak(const std::weak_ptr<Individuum>& a, const std::weak_ptr<Individuum>& b);
	static double sum_weak(double lhs, const std::weak_ptr<Individuum>& rhs);

	friend bool operator==(const std::weak_ptr<Individuum> a, const  std::weak_ptr<Individuum> b);
};

#endif //INDIVIDUUM_H