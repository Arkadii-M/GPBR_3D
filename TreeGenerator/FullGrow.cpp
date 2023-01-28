#include "FullGrow.h"
#include "../GPBR_3D/VariableNode.h"
#include "../GPBR_3D/ConstantNode.h"

FullGrowGenerator::FullGrowGenerator(std::shared_ptr<GpData>& dat, uint min_h, uint max_h):
	TreeGenerator(dat),
	min_height(min_h),
	max_height(max_h),
	terminal_count(0),
	functional_count(0)
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
	return std::make_unique<ExpressionTree>(randTree(h));
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
	return randTree(h);
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::generateSubTree(uint max_h, uint min_h)
{
	return generateSubTree(Random::get<uint>(min_h, max_h));
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::randTree(uint ltc)
{
	if (ltc == 0)
		return createTerminal(ltc);

	if (Random::get<bool>())
		return createFunctional(ltc);

	if (Random::get<int>(1, terminal_count + functional_count) < functional_count)
		return createFunctional(ltc);

	return createTerminal(ltc);
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::createTerminal(uint ltc)
{
	if (Random::get<bool>()) // Create variable
	{
		auto vars = data->getVariables();
		return std::make_unique<VariableNode>(Random::get(vars.begin(), vars.end())->getItem());
	}
	auto consts = data->getConstants();
	return std::make_unique<ConstantNode>(Random::get(consts.begin(), consts.end())->getItem(), data->getEvalNRows(), data->getEvalNCols());
}

std::unique_ptr<IExpressionNode> FullGrowGenerator::createFunctional(uint ltc)
{
	if (Random::get<bool>()) // Create unary node
	{
		auto ufuncs = data->getUnaryFunction();
		auto ufunc = *Random::get(ufuncs.begin(), ufuncs.end());
		return std::make_unique<UnaryNode>(ufunc.getItem(), ufunc.getName(), randTree(ltc - 1));
	}

	auto bfuncs = data->getBinaryFunction();
	auto bfunc = *Random::get(bfuncs.begin(), bfuncs.end());

	return std::make_unique<BinaryNode>(bfunc.getItem(), bfunc.getName(), randTree(ltc - 1), randTree(ltc - 1));
}
