#include "FullGrow.h"
#include "../GP/VariableNode.h"
#include "../GP/ConstantNode.h"

FullGrowGenerator::FullGrowGenerator(std::shared_ptr<GpData>& dat, uint min_h, uint max_h):
	TreeGenerator(dat),
	min_height(min_h),
	max_height(max_h),
	terminal_count(0),
	functional_count(0),
	curr_height(0)
{
	terminal_count = data->getConstants().size() + data->getVariables().size();
	functional_count = data->getBinaryFunction().size() + data->getUnaryFunction().size();
}

std::unique_ptr<ExpressionTree> FullGrowGenerator::generateTree()
{
	return generateTree(min_height, max_height);
}

std::unique_ptr<ExpressionTree> FullGrowGenerator::generateTree(uint h)
{
	curr_height = 0;
	return std::make_unique<ExpressionTree>(randTree(h,0));
}

std::unique_ptr<ExpressionTree> FullGrowGenerator::generateTree(uint max_h, uint min_h)
{
	return generateTree(Random::get<uint>(min_h, max_h));
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::generateSubTree()
{
	return generateSubTree(min_height, max_height);
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::generateSubTree(uint h)
{
	curr_height = 0;
	return randTree(h, 0);
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::generateSubTree(uint max_h, uint min_h)
{
	return generateSubTree(Random::get<uint>(min_h, max_h));
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::randTree(uint ltc, uint curr_h)
{
	if (ltc == 0)
		return createTerminal(ltc, curr_h);

	if (Random::get<bool>(0.5))
		return createFunctional(ltc, curr_h);

	if (Random::get<int>(1, terminal_count + functional_count) < functional_count)
		return createFunctional(ltc, curr_h);

	if(curr_height < min_height)
		return createFunctional(ltc, curr_h);

	return createTerminal(ltc, curr_h);
}
std::unique_ptr<IExpressionNode> FullGrowGenerator::createTerminal(uint ltc, uint curr_h)
{
	curr_height = std::max(curr_height, curr_h);
	return generateTerminal();
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::createFunctional(uint ltc, uint curr_h)
{
	curr_height = std::max(curr_height, curr_h+1);
	if (Random::get<bool>()) // Create unary
	{
		auto unary = generateUnary();
		unary->setLeftSon(randTree(ltc - 1, curr_h + 1));
		return unary;
	}
	auto binary = generateBinary();
	binary->setLeftSon(randTree(ltc - 1, curr_h + 1));
	binary->setRightSon(randTree(ltc - 1, curr_h + 1));
	return binary;
}


//std::unique_ptr<IExpressionNode> FullGrowGenerator::createTerminal(uint ltc)
//{
//	double rand = Random::get<double>(0.0, 1.0 - DBL_EPSILON);
//	if (Random::get<bool>()) // Create variable
//	{
//		auto vars = data->getVariables();
//		auto res = std::find_if(vars.begin(), vars.end(), [&](const GpData::VariableItem& item) {return item.getCumulativeProbability() > rand; });
//		return std::make_unique<VariableNode>(res->getItem());
//	}
//	auto consts = data->getConstants();
//	auto res = std::find_if(consts.begin(), consts.end(), [&](const GpData::ConstItem& item) {return item.getCumulativeProbability() > rand; });
//	return std::make_unique<ConstantNode>(res->getItem());
//
//
//	//if (Random::get<bool>()) // Create variable
//	//{
//	//	auto vars = data->getVariables();
//	//	return std::make_unique<VariableNode>(Random::get(vars.begin(), vars.end())->getItem());
//	//}
//	//auto consts = data->getConstants();
//	////return std::make_unique<ConstantNode>(Random::get(consts.begin(), consts.end())->getItem(), data->getEvalNRows(), data->getEvalNCols());
//	//return std::make_unique<ConstantNode>(Random::get(consts.begin(), consts.end())->getItem());
//}
//
//std::unique_ptr<IExpressionNode> FullGrowGenerator::createFunctional(uint ltc)
//{
//	double rand = Random::get<double>(0.0, 1.0-DBL_EPSILON);
//	if (Random::get<bool>()) // Create unary node
//	{
//		auto ufuncs = data->getUnaryFunction();
//		auto res = std::find_if(ufuncs.begin(), ufuncs.end(), [&](const GpData::UnaryItem& item) {return item.getCumulativeProbability() > rand; });
//		return std::make_unique<UnaryNode>(res->getItem(), res->getName(), randTree(ltc - 1));
//	}
//
//	auto bfuncs = data->getBinaryFunction();
//	auto res = std::find_if(bfuncs.begin(), bfuncs.end(), [&](const GpData::BinaryItem& item) {return item.getCumulativeProbability() > rand; });
//	return std::make_unique<BinaryNode>(res->getItem(), res->getName(), randTree(ltc - 1), randTree(ltc - 1));
//	//if (Random::get<bool>()) // Create unary node
//	//{
//	//	auto ufuncs = data->getUnaryFunction();
//	//	auto ufunc = *Random::get(ufuncs.begin(), ufuncs.end());
//	//	return std::make_unique<UnaryNode>(ufunc.getItem(), ufunc.getName(), randTree(ltc - 1));
//	//}
//
//	//auto bfuncs = data->getBinaryFunction();
//	//auto bfunc = *Random::get(bfuncs.begin(), bfuncs.end());
//
//	//return std::make_unique<BinaryNode>(bfunc.getItem(), bfunc.getName(), randTree(ltc - 1), randTree(ltc - 1));
//}