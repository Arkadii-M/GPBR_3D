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
#include "../BREvaluate/MseError.h"
#include <iostream>
#include <cassert>
#include <string.h>
#include <memory>


#include "../GP/GpData.h"
#include "../TreeGenerator/PTC-1.h"
#include "../GeneticOperators/ScaleMutation.h"

#define SAME_PROB 1.0


template<typename T,typename D>
void CalculateCumulativeProbabilities(std::vector<GpItem<T, D>>& items)
{
	double sum = std::accumulate(items.begin(), items.end(), 0.0, [](double lhs,const GpItem<T,D>& item) {
			return lhs + item.getProbability();
		});
	std::accumulate(items.begin(), items.end(), 0.0,
		[&](double lhs, GpItem<T,D>& item) {
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

	//[](const arma::dmat& x, const arma::dmat& y) {return x + y; }
	auto plus_derivative = [](
		const arma::dmat& x,
		const arma::dmat& y,
		const arma::dmat& dx,
		const arma::dmat& dy) 
	{return dx + dy; };


	//auto binary_functions = std::vector< GpData::BinaryItem>();
	//binary_functions.push_back(GpData::BinaryItem(
	//	[](const arma::dmat& x, const arma::dmat& y) {return x + y; },"+",SAME_PROB,
	//	[](	const arma::dmat& x,const arma::dmat& y, 
	//		const arma::dcube& dx, const arma::dcube& dy) {return dx + dy; }));

	//binary_functions.push_back(GpData::BinaryItem(
	//	[](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", SAME_PROB,
	//	[](const arma::dmat& x, const arma::dmat& y,
	//		const arma::dcube& dx, const arma::dcube& dy) {return dx - dy; }));
	//binary_functions.push_back(GpData::BinaryItem(
	//	[](const arma::dmat& x, const arma::dmat& y) {return x % y; }, "*", SAME_PROB,
	//	[](const arma::dmat& x, const arma::dmat& y,
	//		const arma::dcube& dx, const arma::dcube& dy) {return dx.each_slice() % y - x % dy.each_slice(); }));
	//binary_functions.push_back(GpData::BinaryItem(
	//	[](const arma::dmat& x, const arma::dmat& y) {return x / y; }, "/", 0.2,
	//	[](const arma::dmat& x, const arma::dmat& y,
	//		const arma::dcube& dx, const arma::dcube& dy) {return dx.each_slice() /y - (x/pow(y,2))%dy.each_slice(); }));
	//binary_functions.push_back(GpData::BinaryItem(
	//	[](const arma::dmat& x, const arma::dmat& y) {return pow(x,y); }, "^", 0.6,
	//	[](const arma::dmat& x, const arma::dmat& y,
	//		//const arma::dmat& dx, const arma::dmat& dy) {return pow(x,y)%log(x)%dy + y%pow(x,y-1)%dx; }));
	//		//const arma::dcube& dx, const arma::dcube& dy) {return ( log(x)%dy + (y%dx)/x )% pow(x, y); }));
	//		const arma::dcube& dx, const arma::dcube& dy) {
	//			return (log(x) % dy.each_slice() + (y % dx.each_slice()).each_slice() / x).eval().each_slice() % pow(x, y);
	//	}));
	auto binary_functions = std::vector< GpData::BinaryItem>();
	binary_functions.push_back(GpData::BinaryItem(
		[](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& y,
			const arma::dmat& dx, const arma::dmat& dy) {return dx + dy; }));

	binary_functions.push_back(GpData::BinaryItem(
		[](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& y,
			const arma::dmat& dx, const arma::dmat& dy) {return dx - dy; }));

	binary_functions.push_back(GpData::BinaryItem(
		[](const arma::dmat& x, const arma::dmat& y) {return x % y; }, "*", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& y,
			const arma::dmat& dx, const arma::dmat& dy) {return dx % y - x % dy; }));

	binary_functions.push_back(GpData::BinaryItem(
		[](const arma::dmat& x, const arma::dmat& y) {return x / y; }, "/", 0.2,
		[](const arma::dmat& x, const arma::dmat& y,
			const arma::dmat& dx, const arma::dmat& dy) {return dx / y - (x / pow(y, 2)) % dy; }));

	binary_functions.push_back(GpData::BinaryItem(
		[](const arma::dmat& x, const arma::dmat& y) {return pow(x, y); }, "^", 0.6,
		[](const arma::dmat& x, const arma::dmat& y,
			//const arma::dmat& dx, const arma::dmat& dy) {return pow(x,y)%log(x)%dy + y%pow(x,y-1)%dx; }));
			//const arma::dcube& dx, const arma::dcube& dy) {return ( log(x)%dy + (y%dx)/x )% pow(x, y); }));
			const arma::dmat& dx, const arma::dmat& dy) {
				return (log(x) % dy+ (y % dx) / x).eval() % pow(x, y);
		}));
	CalculateCumulativeProbabilities(binary_functions);


	//auto unary_functions = std::vector<GpData::UnaryItem>();
	//unary_functions.push_back(GpData::UnaryItem(
	//	[](const arma::dmat& val) {return arma::sin(val); }, "sin", SAME_PROB,
	//	[](const arma::dmat& x, const arma::dcube& dx) {return arma::cos(x)%dx.each_slice(); }));
	//unary_functions.push_back(GpData::UnaryItem(
	//	[](const arma::dmat& val) {return arma::cos(val); }, "cos", SAME_PROB,
	//	[](const arma::dmat& x, const arma::dcube& dx) {return -arma::sin(x) % dx.each_slice(); }));
	////unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::log(val); }, "log", 0.1));
	//unary_functions.push_back(GpData::UnaryItem(
	//	[](const arma::dmat& val) {return arma::sqrt(val); },"sqrt", SAME_PROB,
	//	[](const arma::dmat& x, const arma::dcube& dx) {return dx.each_slice() /(2*sqrt(x)); }));
	auto unary_functions = std::vector<GpData::UnaryItem>();
	unary_functions.push_back(GpData::UnaryItem(
		[](const arma::dmat& val) {return arma::sin(val); }, "sin", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& dx) {return arma::cos(x) % dx; }));
	unary_functions.push_back(GpData::UnaryItem(
		[](const arma::dmat& val) {return arma::cos(val); }, "cos", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& dx) {return -arma::sin(x) % dx; }));
	//unary_functions.push_back(GpData::UnaryItem([](const arma::dmat& val) {return arma::log(val); }, "log", 0.1));
	unary_functions.push_back(GpData::UnaryItem(
		[](const arma::dmat& val) {return arma::sqrt(val); }, "sqrt", SAME_PROB,
		[](const arma::dmat& x, const arma::dmat& dx) {return dx/ (2 * sqrt(x)); }));
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


	// define data
	auto problem_data = std::make_shared<ProblemData>(Gamma1, Gamma2, Gamma1Cond, Gamma2Cond, collocation);
	

	// define helper
	auto helper = std::make_shared<ProblemHelper>(problem_data);

	// define points collocation on boudary and sources
	auto coll_boundary = problem_data->getBoundaryCollocation();
	auto coll_sources = problem_data->getSourcesCollocation();

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

	// find data on external boundary
	arma::dcolvec u_on_g2;
	helper->uOnG2(G1_boundary, G1_sources, u_on_g2);


	/// Form test condition
	// use them as test condition
	MFS_BC Gamma2TestCond = MFS_BC([&u_on_g2](arma::dcube X){ return u_on_g2; });// TODO: implement noise
	problem_data->setG2TestCondition(Gamma2TestCond);


	// define an error function
	std::shared_ptr<ErrorFunction> mse_error = std::make_unique<MseError>();


	// calculate norm for the fixed G1 values. Check if error is zero
	auto exact_f_data = problem_data->getG2TestConditionValues();

	double test_error = mse_error->evaluate(exact_f_data, u_on_g2);
	std::cout << "test error: " << test_error << "\n";
	assert(test_error < 1e-5);// Note. There is no noise. TODO: change when noise will be implemented



	
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
		helper,
		mse_error,
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