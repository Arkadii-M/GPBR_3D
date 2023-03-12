#pragma once
#ifndef INDIVIDUUM_H
#define INDIVIDUUM_H

#include "ExpressionTree.h"
#include "IndividuumData.h"

class Individuum
{
private:
	std::unique_ptr<ExpressionTree> tree;
	double fitness;
	bool is_calculated;

	//TODO: create a class to store the problem data
	std::unique_ptr<IndividuumData> data;
public:
	Individuum(std::unique_ptr<ExpressionTree> tree);
	Individuum(const Individuum& rhs);

	double getFintness() const;
	void setFitness(double fit);

	bool isCalculated() const;
	void setCalculated(bool calc);

	std::unique_ptr<ExpressionTree>& getTree();
	void setTree(std::unique_ptr<ExpressionTree> tree);

	std::unique_ptr<IndividuumData>& getData();
	void setData(std::unique_ptr<IndividuumData> data);

	// TODO: add comapare and accumulate for STL.
	static bool cmp_weak(const std::weak_ptr<Individuum>& a, const std::weak_ptr<Individuum>& b);
	static double sum_weak(double lhs, const std::weak_ptr<Individuum>& rhs);

	friend bool operator==(const std::weak_ptr<Individuum> a, const  std::weak_ptr<Individuum> b);
};

#endif //INDIVIDUUM_H