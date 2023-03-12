//#include "BackPropagationMutation.h"
//
//BackPropagationMuation::BackPropagationMuation(std::shared_ptr<ProblemHelper> helper,MFSCollocation collocation,uint num_iter, double learning_rate, double prob):
//	GeneticOpretator(prob),
//	helper(helper),
//	learning_rate(learning_rate),
//	num_iter(num_iter),
//	collocation(collocation),
//	boundary_thetha(collocation.getBoundary().getThetha()),
//	boundary_phi(collocation.getBoundary().getPhi()),
//	source_thetha(collocation.getSources().getThetha()),
//	source_phi(collocation.getSources().getPhi()),
//
//
//{
//}
//
//void BackPropagationMuation::apply(std::weak_ptr<Individuum> individuum)
//{
//	auto& tree = individuum.lock()->getTree();
//
//
//	auto constants_list = tree->filterNodesIdexes(std::make_unique<BackPropagationMuation::Filter>());
//	uint n_consts = constants_list.size();
//
//	if (n_consts == 0)// no constants
//		return;
//
//
//	// Calculate partial derivatives of r(theta,phi,c) with respect to c where c are 'variables' ( make this assumption for gradient descent)
//	const TreeDerivativeInfo derivatives_info = TreeDerivativeInfo(constants_list);
//	auto boundary_partial_derivatives = tree->autoDiffReverse(boundary_thetha,boundary_phi,derivatives_info);
//	auto r_boundary = boundary_partial_derivatives.getElement().as_col();
//	auto dr_boundary = boundary_partial_derivatives.getDerivative();
//
//	// Also calculate values on the boundary
//	auto r_sources = tree->evaluate(source_thetha, source_phi).as_col();
//
//	auto Gamma1 = helper->getGamma1();
//	auto G2_boundary = helper->getGamma2Boundary();
//	auto f_vals = helper->getGamma2TestCondition()(G2_boundary);
//
//	auto update_vals = getBackpropagationDerivative(Gamma1, G2_boundary, r_boundary, dr_boundary, r_sources, f_vals);
//	for (uint i = 0; i < constants_list.size(); i++)
//	{
//		auto observer = tree->getNodeObserver(constants_list.at(i));
//		ExpressionTree::NodeObserve::SwapSubTrees(observer,
//			std::make_unique<ConstantNode>(std::stod(observer->getName()) - learning_rate*update_vals(0, 0, i)));
//	}
//
//}
//void BackPropagationMuation::makeBackpropagationStep(
//	StarLike3DBoundary& Gamma1,
//	const arma::dcube G2_boundary,
//	const arma::dcolvec& r_boundary,
//	const arma::dcube& dr_boundary, 
//	const arma::dcolvec& r_sources,
//	const arma::dcolvec& f_vals)
//{
//
//	arma::dcube G1_boundary = Gamma1(r_boundary, boundary_thetha, boundary_phi);
//	arma::dcube G1_sources = Gamma1(r_sources, source_thetha, source_phi);
//
//	arma::dcube G1_derivatives = arma::dcube(1, 1, dr_boundary.n_slices);
//
//	for (uint i = 0; i < dr_boundary.n_slices; ++i)
//		G1_derivatives.slice(i) = Gamma1(dr_boundary.slice(i).as_col(), boundary_thetha, boundary_phi);
//
//	// Solve system and find lambda constants
//	auto lambda = arma::solve(helper->formMatrix(G1_boundary, G1_sources), helper->formColumn(G1_boundary), arma::solve_opts::no_approx);
//
//	auto u = helper->uApprox(lambda, G2_boundary, G1_sources);
//	auto du = helper->partialU(lambda, G2_boundary, G1_derivatives, G1_sources);
//
//	// Error functions is 2/N * Sum((u_k-f_k)^2)
//	return arma::sum((u - f_vals) % du.each_slice(),0); // sum of column of each slices
//}
//
//
//bool BackPropagationMuation::Filter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
//{
//	return 	IsLeaf()(node) && IsNumber()(node);
//}
//
