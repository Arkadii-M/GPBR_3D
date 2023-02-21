#include "TreeGenerator.h"

TreeGenerator::TreeGenerator(std::shared_ptr<GpData>& dat):
	data(dat)
{
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateTerminal()
{
	if (Random::get<bool>()) // Create variable
		return generateVariable();
	return generateConstant();
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateFunctional()
{
	if (Random::get<bool>()) // Create unary node
		return generateUnary();
	return generateBinary();
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateConstant()
{
	double rand = Random::get<double>(0.0, 1.0 - DBL_EPSILON);
	auto consts = data->getConstants();
	auto res = std::find_if(consts.begin(), consts.end(), [&](const GpData::ConstItem& item) {return item.getCumulativeProbability() > rand; });
	return std::make_unique<ConstantNode>(res->getItem());
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateVariable()
{
	double rand = Random::get<double>(0.0, 1.0 - DBL_EPSILON);
	auto vars = data->getVariables();
	auto res = std::find_if(vars.begin(), vars.end(), [&](const GpData::VariableItem& item) {return item.getCumulativeProbability() > rand; });
	return std::make_unique<VariableNode>(res->getItem());
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateUnary()
{
	double rand = Random::get<double>(0.0, 1.0 - DBL_EPSILON);
	auto ufuncs = data->getUnaryFunction();
	auto res = std::find_if(ufuncs.begin(), ufuncs.end(), [&](const GpData::UnaryItem& item) {return item.getCumulativeProbability() > rand; });
	return std::make_unique<UnaryNode>(res->getItem(), res->getName(), nullptr);
}

std::unique_ptr<IExpressionNode> TreeGenerator::generateBinary()
{
	double rand = Random::get<double>(0.0, 1.0 - DBL_EPSILON);
	auto bfuncs = data->getBinaryFunction();
	auto res = std::find_if(bfuncs.begin(), bfuncs.end(), [&](const GpData::BinaryItem& item) {return item.getCumulativeProbability() > rand; });
	return std::make_unique<BinaryNode>(res->getItem(), res->getName(), nullptr, nullptr);
}
