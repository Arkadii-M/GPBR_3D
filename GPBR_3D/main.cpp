//#include <iostream>
//
//#include "../GP/ExpressionTree.h"
//#include "../GP/GpData.h"
//#include "../GP/GpParser.h"
//#include "../GP/TempNode.h"
////#include "../GP/GpParser.h"
//
//struct RootFilter : public ExpressionTree::NodeFilter
//{
//	virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override {
//		return node->getNum() != 1;
//	}
//};
//
//int main()
//{
//	std::unique_ptr<IExpressionNode> thetha = std::make_unique<VariableNode>("thetha");
//	std::unique_ptr<IExpressionNode> phi = std::make_unique<VariableNode>("phi");
//
//	std::unique_ptr<IExpressionNode> cos = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "cos", std::move(thetha));
//	std::unique_ptr<IExpressionNode> sin = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "sin", std::move(phi));
//
//
//	std::unique_ptr<IExpressionNode> plus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", std::move(cos), std::move(sin));
//
//
//	std::unique_ptr<IExpressionNode> thetha1 = std::make_unique<VariableNode>("thetha");
//	std::unique_ptr<IExpressionNode> phi1 = std::make_unique<VariableNode>("phi");
//
//	std::unique_ptr<IExpressionNode> exp = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "exp", std::move(thetha1));
//	std::unique_ptr<IExpressionNode> tan = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "tan", std::move(phi1));
//
//
//	std::unique_ptr<IExpressionNode> minus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "-", std::move(exp), std::move(tan));
//
//	std::unique_ptr<ExpressionTree> tree1 = std::make_unique<ExpressionTree>(std::move(plus));
//	std::unique_ptr<ExpressionTree> tree2 = std::make_unique<ExpressionTree>(std::move(minus));
//
//	std::cout << tree1->print() << "\n";
//	std::cout << tree2->print() << "\n\n\n";
//
//	auto t1_o = tree1->getRootObserver()->getLeft();
//	auto t2_o = tree2->getRootObserver()->getRight();
//
//	ExpressionTree::ReplaceNodes(tree1,tree2,t1_o, t2_o);
//
//	std::cout << tree1->print() << "\n";
//	std::cout << tree2->print() << "\n";
//	//std::cout << t1_o.print() << "\n";
//	//std::cout << t2_o.print() << "\n";
//
//	//ExpressionTree::SwapNodesAtPositions(tree1, tree2, 2, 4);
//
//
//	//std::cout << tree1->getRoot()->toString() << "\n";
//	//std::cout << tree2->getRoot()->toString() << "\n";
//
//	//std::unique_ptr<ExpressionTree::NodeFilter> root_filter = std::make_unique<RootFilter>();
//	//auto ret_vec = tree1->filterNodesIdexes(root_filter);
//
//
//	//const arma::uword n_repeat = 1;
//	//GpData::Bset bset = GpData::Bset();
//	//bset.insert(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", 1.0));
//	//bset.insert(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", 1.0));
//
//	//GpData::Uset uset = GpData::Uset();
//	//uset.insert(GpData::UnaryItem([](const arma::dmat& val) {return arma::cos(val); }, "cos", 1.0));
//	//uset.insert(GpData::UnaryItem([](const arma::dmat& val) {return arma::sin(val); }, "sin", 1.0));
//
//	//GpData::Vset vset = GpData::Vset();
//	//vset.insert(GpData::VariableItem("thetha","thetha", 1.0));
//	//vset.insert(GpData::VariableItem("phi", "phi", 1.0));
//
//	//GpData::Cset cset = GpData::Cset();
//	//cset.insert(GpData::ConstItem(0.0, "0.0", 1.0));
//
//
//	//auto gp_data = std::make_shared<GpData>(bset,uset,vset,cset, n_repeat, n_repeat);
//	//auto gp_parser = GpParser(gp_data);
//
//	//std::unique_ptr<IExpressionNode> thetha = std::make_unique<VariableNode>("thetha");
//	//std::unique_ptr<IExpressionNode> phi = std::make_unique<VariableNode>("phi");
//	//std::unique_ptr<IExpressionNode> thetha1 = std::make_unique<VariableNode>("thetha");
//	//std::unique_ptr<IExpressionNode> phi1 = std::make_unique<VariableNode>("phi");
//
//	//std::unique_ptr<IExpressionNode> minus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", std::move(thetha1), std::move(phi1));
//
//	//std::unique_ptr<IExpressionNode> cos = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "cos", std::move(minus));
//	//std::unique_ptr<IExpressionNode> sin = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "sin", std::move(phi));
//
//
//	//std::unique_ptr<IExpressionNode> plus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", std::move(cos), std::move(sin));
//
//
//	//std::cout << "Constructed tree:\n" << plus->toString() << "\n";
//
//	//std::unique_ptr<ExpressionTree> tree1 = std::make_unique<ExpressionTree>(std::move(plus));
//
//
//	//json tree_json = gp_parser.parseTreeToJson(tree1);
//	////std::cout << tree_json.dump(4) << "\n";
//	//auto tree_from_json = gp_parser.parseJsonToTree(tree_json);
//
//	//std::cout << "From json:\n" << tree_from_json->getRoot()->toString() << "\n";
//
//
//	return 0;
//}


#include "../RmodelGP/RModelGp.h"
#include "../BREvaluate/EvaluateCpu.h"
#include "../RmodelGP/RModelSelector.h"
#include "../SolutionProcessor/SolutionProcessor.h"
#include "../SolutionProcessor/SolutionPlotter.h"
#include "../GeneticOperators/UniformCrossover.h"
#include "../GeneticOperators/OnePointCrossover.h"
#include "../GeneticOperators/TerminalMutation.h"
#include "../GeneticOperators/SwapMutation.h"
#include "../GeneticOperators/ShrinkMutatation.h"
#include "../GeneticOperators/NodeReplaceMutation.h"
#include "../GeneticOperators/HoistMutation.h"
#include "../GeneticOperators/ConstMutation.h"
#include "../TreeGenerator/FullGrow.h"
#include "../BREvaluate/ProblemHelper.h"
#include "../BREvaluate/MFSCollocation.h"
#include "../BREvaluate/SphereBoundary.h"
#include "../BREvaluate/BoundaryCondtition.h"
#include "../BREvaluate/StarlikeBoundary.h"
#include "../GP/GpParser.h"
#include <iostream>
#include <cassert>
#include <string.h>
#include <memory>


#include "../GP/GpData.h"
#include "../TreeGenerator/PTC-1.h"
#include "../GeneticOperators/ScaleMutation.h"

#define SAME_PROB 1.0


template<typename T>
void CalculateCumulativeProbabilities(std::vector<GpItem<T>>& items)
{
	double sum = std::accumulate(items.begin(), items.end(), 0.0, [](double lhs,const GpItem<T>& item) {
			return lhs + item.getProbability();
		});
	std::accumulate(items.begin(), items.end(), 0.0,
		[&](double lhs, GpItem<T>& item) {
			double res = lhs + item.getProbability();
			item.setCumulativeProbability(res / sum);
		return res;
		});
	//std::sort(items.begin(), items.end(),
	//	[](const GpItem<T>& lhs, const GpItem<T>& rhs) 
	//	{
	//		return lhs.getCumulativeProbability() < rhs.getCumulativeProbability(); 
	//	});
	std::sort(items.begin(), items.end());
}

int main()
{
	using uint = unsigned int;

	const uint pop_size = 500;
	// number of collocation points
	const uint n_boundary = 16;
	const uint n_sources = 16;

	const double mutate_prob = 0.35;
	const double cross_prob = 0.75;

	const uint tournament = 3;
	const uint r_param = (uint)((float)pop_size * 0.4);

	const double curvature_threshold = 1.0;// TODO: calculate

	const uint min_tree_h = 10;
	const uint max_tree_h = 20;

	const uint n_thetha_plot = 16;
	const uint n_phi_plot = 32;

	const double const_min = -50;
	const double const_max = 50;
	const double step = 0.5;
	assert(const_min < const_max);
	assert(step > 0);


	/* Configure Gp data*/

	auto binary_functions = std::vector< GpData::BinaryItem>();
	binary_functions.push_back(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", SAME_PROB));
	binary_functions.push_back(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", SAME_PROB));
	binary_functions.push_back(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x % y; }, "*", SAME_PROB));
	binary_functions.push_back(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x / y; }, "/", 0.2));
	binary_functions.push_back(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return pow(x,y); }, "^", 0.6));
	CalculateCumulativeProbabilities(binary_functions);


	auto unary_functions = std::vector<GpData::UnaryItem>();
	unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::sin(val); }, "sin", SAME_PROB));
	unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::cos(val); }, "cos", SAME_PROB));
	//unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::log(val); }, "log", 0.1));
	unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::sqrt(val); },"sqrt", SAME_PROB));
	//unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::exp(val); }, "exp", 0.1));
	//unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::abs(val); }, "abs", 0.1));
	CalculateCumulativeProbabilities(unary_functions);

	auto variables = std::vector<GpData::VariableItem>();
	variables.push_back(GpData::VariableItem("thetha","thetha", SAME_PROB));
	variables.push_back(GpData::VariableItem("phi", "phi", 0.2));// TODO: use small probability
	CalculateCumulativeProbabilities(variables);

	auto constants = std::vector<GpData::ConstItem>();
	for(double curr = const_min; curr < const_max;curr+=step)
		constants.push_back(GpData::ConstItem(curr, std::to_string(curr), SAME_PROB));
	CalculateCumulativeProbabilities(constants);

	auto gp_data = std::make_shared<GpData>(
		GpData::Bset(binary_functions.begin(), binary_functions.end()),
		GpData::Uset(unary_functions.begin(), unary_functions.end()),
		GpData::Vset(variables.begin(), variables.end()),
		GpData::Cset(constants.begin(), constants.end()));
	auto gp_parser = std::make_shared<GpParser>(gp_data);


	/*	define boundaries	*/
	// Internal boundary
	StarLike3DBoundary Gamma1 = StarLike3DBoundary();
	MFS_BC Gamma1Cond = MFS_BC([](arma::Cube<double> X) {return arma::dcolvec(X.n_rows,arma::fill::zeros); });

	// External boundary
	SphereBoundary Gamma2 = SphereBoundary(5);
	MFS_BC Gamma2Cond = MFS_BC([](arma::Cube<double> X) {return arma::dcolvec(X.n_rows, arma::fill::value(3.0)); });// Neuman condition

	// define collocation
	MFSCollocation collocation = MFSCollocation(n_boundary,n_sources);

	// define helper
	auto helper = std::make_unique<ProblemHelper>(collocation, Gamma1, Gamma1Cond, Gamma2, Gamma2Cond);

	// define points collocation on boudary and sources
	auto coll_boundary = collocation.getBoundary();
	auto coll_sources = collocation.getSources();

	rfunc_vec r_exact = [](arma::dcolvec thetha, arma::dcolvec phi) {
		arma::dcolvec res = 2 + sqrt(4.25 + 3 * cos(3 * thetha));
		return res;
	};
	const std::string exact_str = "2+sqrt(4.25 + 3*cos(3*thetha))";

	//rfunc_vec r_exact = [](arma::dcolvec thetha, arma::dcolvec phi) {
	//	arma::dcolvec res = 2*sqrt(cos(2*thetha)+sqrt(2-pow(sin(2 * thetha),2)));
	//	return res;
	//};
	//const std::string exact_str = "2.*sqrt(cos(2.*thetha).+sqrt(2.-sin(2.*thetha).^2))";



	// calculate G1 on boundary and sources
	auto coll_vals = r_exact(coll_boundary.getThetha(), coll_boundary.getPhi());
	auto source_vals = r_exact(coll_sources.getThetha(), coll_sources.getPhi());

	arma::dcube G1_boundary = Gamma1(coll_vals, coll_boundary.getThetha(), coll_boundary.getPhi());
	arma::dcube G1_sources  = Gamma1(source_vals, coll_sources.getThetha(), coll_sources.getPhi());

	// form and solve equation
	arma::dmat A = helper->formMatrix(G1_boundary, G1_sources);
	arma::dcolvec b = helper->formColumn(G1_boundary);

	arma::dcolvec lambda = arma::solve(A, b);
	//lambda.raw_print("lambda = ");


	// calculate data on G2
	arma::dcube G2_boundary = Gamma2(coll_boundary.getThetha(), coll_boundary.getPhi());
	arma::dcolvec u_on_g2 = helper->uApprox(lambda, G2_boundary, G1_sources);
	//u_on_g2.print("Uapprox on G2:");

	/// Form test condition
	// use them as test condition
	MFS_BC Gamma2TestCond = MFS_BC([&u_on_g2](arma::dcube X){ return u_on_g2; });// TODO: implement noise
	helper->setTestCondition(Gamma2TestCond);

	// calculate norm for the fixed G1 values. Check if error is zero
	double test_error = helper->l2Norm(G1_boundary, G1_sources);
	std::cout << "test error: " << test_error << "\n";
	assert(helper->l2Norm(G1_boundary, G1_sources)< 1e-5);// Note. There is no noise. TODO: change when noise will be implemented
	/*	define tree generators	*/
	auto full_grow_generator = std::make_shared<FullGrowGenerator>(gp_data, min_tree_h, max_tree_h);
	//auto ptc1_generator = std::make_shared<PTC_1_Generator>(gp_data, 20, max_tree_h);

	/*	define genetic operators */
	// mutation operators
	std::vector<std::unique_ptr<GeneticOpretator>> mutate_operators = std::vector<std::unique_ptr<GeneticOpretator>>();
	mutate_operators.push_back(std::make_unique<ConstantMutation>(-1.0,1.0,0.1,0.8));
	mutate_operators.push_back(std::make_unique<HoistMutation>(min_tree_h,0.1));
	mutate_operators.push_back(std::make_unique<NodeReplaceMutation>(full_grow_generator,0.8));
	mutate_operators.push_back(std::make_unique<ShrinkMutation>(full_grow_generator,0.1));
	mutate_operators.push_back(std::make_unique<SwapMutation>(0.1));
	mutate_operators.push_back(std::make_unique<TerminalMutation>(full_grow_generator,0.7));
	mutate_operators.push_back(std::make_unique<ScaleMutation>(gp_data,1e-3, 0.1));
	
	 
	//// crossover operators
	std::vector<std::unique_ptr<GeneticOpretator>> crossove_operators = std::vector<std::unique_ptr<GeneticOpretator>>();
	crossove_operators.push_back(std::make_unique<OnePointCrossover>(0.9));
	crossove_operators.push_back(std::make_unique<UniformCrossover>(0.5,0.8));

	// define solution plotter and  processor
	auto plotter = std::make_unique<SolutionPlotter>(exact_str, n_thetha_plot, n_phi_plot, SolutionPlotter::SolutionPlotMode::Both);
	auto processor = std::make_unique<SolutionProcesser>("./", std::move(plotter),gp_parser);

	// define selector
	auto selector = std::make_unique<RModelSelector>(mutate_prob, cross_prob, r_param, tournament);

	std::unique_ptr<Evaluator> cpu_eval = std::make_unique<EvaluateCpu>(
		std::move(helper),
		std::make_unique<MeshIntersection>(n_boundary, n_boundary, 1, 1),// TODO: test
		std::make_unique<BezierCurvature>(n_boundary-1, arma::linspace<arma::drowvec>(0, 1, 50), curvature_threshold)
		);

	auto gp_model = RmodelGp(
		std::move(cpu_eval),
		full_grow_generator,
		std::move(selector),
		mutate_operators, crossove_operators,
		std::move(processor),500,50,1e-5);

	gp_model.generatePopulation(pop_size);
	gp_model.execute(2000);
	return 0;
}