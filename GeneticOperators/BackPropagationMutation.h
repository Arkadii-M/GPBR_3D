//#pragma once
//#include "../GP/random.hpp"
//#include "../GP/GeneticOperator.h"
//#include "NodeFilter.h"
//#include "../GP/GpData.h"
//#include "../BREvaluate/MFSCollocation.h"
//#include "../BREvaluate/ProblemHelper.h"
//#include "../GP/ConstantNode.h"
//#ifndef BACKPROPAGATION_MUTATION_H
//#define BACKPROPAGATION_MUTATION_H
//
//using Random = effolkronium::random_static;
//class BackPropagationMuation :public GeneticOpretator
//{
//	//TODO: define and implement
//	const uint num_iter;
//	const double learning_rate;
//	const MFSCollocation collocation;
//	std::shared_ptr<ProblemHelper> helper;
//
//	const arma::dcolvec boundary_thetha;
//	const arma::dcolvec boundary_phi;
//	const arma::dcolvec source_thetha;
//	const arma::dcolvec source_phi;
//
//public:
//	BackPropagationMuation(std::shared_ptr<ProblemHelper> helper,MFSCollocation collocation,uint num_iter, double learning_rate,double prob = 1.0);
//
//	virtual void apply(std::weak_ptr<Individuum> individuum) override;
//
//
//private:
//	void makeBackpropagationStep(
//		StarLike3DBoundary & Gamma1,
//		const arma::dcube G2_boundary,
//		const arma::dcolvec& r_boundary,
//		const arma::dcube& dr_boundary,
//		const arma::dcolvec& r_sources,
//		const arma::dcolvec& f_vals);
//	struct Filter : public ExpressionTree::NodeFilter
//	{
//		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override;
//	};
//};
//
//
//#endif // !BACKPROPAGATION_MUTATION_H
