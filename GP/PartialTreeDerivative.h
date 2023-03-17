#pragma once
#include <vector>
#include <armadillo>
#ifndef PARTIAL_DERIVATIVE_H
#define PARTIAL_DERIVATIVE_H

typedef unsigned int uint;
//class TreeDerivativeInfo
//{
//private:
//	std::vector<uint> diff_ids;
//public:
//	TreeDerivativeInfo(std::vector<uint> ids);
//	bool inDiffIdArray(const uint id) const;
//	uint getNelements() const;
//};
//class TreeDerivative
//{
//private:
//	const arma::dmat x;
//	const arma::dcube dx;
//
//public:
//	TreeDerivative(arma::dmat& x, arma::dcube& dx);
//
//	const arma::dmat& getValues() const;
//	const arma::dcube& getDerivatives() const;
//
//};

class TreeDerivative
{
public:
	enum class PartialDerivativeStrategy
	{
		OnlyConstsDerivative,
	};

	class LeafDerivative
	{
	private:
		const uint id;
		arma::dmat dx;
		arma::dmat dNotx;
	public:
		LeafDerivative(uint id, arma::dmat dx);
		uint getId() const;

		arma::dmat getDerivative() const;
		arma::dmat getOtherDerivative() const;

		void setDerivative(arma::dmat & dx);
		void setOtherDerivative(arma::dmat& dNotx);

	};
private:
	arma::dmat values;
	std::vector<LeafDerivative> derivatives;
public:
	TreeDerivative(arma::dmat vals);
	TreeDerivative(arma::dmat vals, LeafDerivative derivative);

	void setValues(arma::dmat vals);
	arma::dmat getValues() const;

	std::vector<LeafDerivative> getDerivatives() const;


	static void ConcatDerivatives(TreeDerivative& first, TreeDerivative& second);



};
#endif // !PARTIAL_DERIVATIVE_H
