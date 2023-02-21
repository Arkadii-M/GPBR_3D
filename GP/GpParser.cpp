#include "GpParser.h"

GpParser::GpParser(std::shared_ptr<GpData> data):
	data(data)
{
}

json GpParser::parseTreeToJson(std::unique_ptr<ExpressionTree>& tree)
{
	return parseSubTreeToJson(tree->getRootObserver());
}
json GpParser::parseSubTreeToJson(std::unique_ptr<ExpressionTree::NodeObserve> node)
{
	if (node->isNull())
		return nullptr;
	return {
		{"name",	node->getName()},
		{"left", parseSubTreeToJson(node->getLeft())},
		{"right", parseSubTreeToJson(node->getRight())}
	};
}

std::unique_ptr<ExpressionTree> GpParser::parseJsonToTree(json tree)
{
	return std::make_unique<ExpressionTree>(parseJsonToSubTree(tree));
}

std::unique_ptr<IExpressionNode> GpParser::parseJsonToSubTree(json subtree)
{
	if (subtree.is_null())
		return nullptr;
	
	auto& name = subtree["name"];
	auto& left = subtree["left"];
	auto& right = subtree["right"];

	//if (name.is_number()) // Constant
	//	return std::make_unique<ConstantNode>((double)name, data->getEvalNRows(), data->getEvalNCols());
	if (name.is_number()) // Constant
		return std::make_unique<ConstantNode>((double)name);


	if (left.is_null())
		return std::make_unique<VariableNode>((std::string)name);


	if (right.is_null())// Unary function
	{
		auto Ufuncs = data->getUnaryFunction();
		auto ufunc = std::find_if(Ufuncs.begin(), Ufuncs.end(), [&name](const GpItem<dmatUnaryFunc> item) {
			return item.getName() == (std::string)name;
			});
		if (ufunc == Ufuncs.end())
			throw std::invalid_argument(std::format("No unary function with name {} found in set", (std::string)name));

		return std::make_unique<UnaryNode>(ufunc->getItem(), (std::string)name, parseJsonToSubTree(left));
	}
	//Binary function
	auto Bfuncs = data->getBinaryFunction();
	auto bfunc = std::find_if(Bfuncs.begin(), Bfuncs.end(), [&name](const GpItem<dmatBinaryFunc> item) {
		return item.getName() == (std::string)name;
		});
	if (bfunc == Bfuncs.end())
		throw std::invalid_argument(std::format("No binary function with name {} found in set", (std::string)name));

	return std::make_unique<BinaryNode>(bfunc->getItem(), (std::string)name, parseJsonToSubTree(left), parseJsonToSubTree(right));
}


json GpParser::parseIndividuumToJson(std::weak_ptr<Individuum> individuum)
{
	return {
	{"fitness",	individuum.lock()->getFintness()},
	{"tree", parseTreeToJson(individuum.lock()->getTree())},
	};
}
std::shared_ptr<Individuum> GpParser::parseJsonToIndividuum(json individuum)
{
	auto& fitness = individuum["fitness"];
	auto& tree = individuum["tree"];
	auto ind = std::make_shared<Individuum>(parseJsonToTree(tree));
	ind->setFitness((double)fitness);
	ind->setCalculated(true);
	return ind;
}



json GpParser::parsePopulationToJson(Population& population) {
	json res;
	auto it = population.begin();
	while (it != population.end())
	{
		res.push_back(parseIndividuumToJson(*it));
		it++;
	}
	return res;
}
void GpParser::parseJsonToPopulation(json jpopulation, Population& population)
{
	auto jpopIt = jpopulation.begin();
	while (jpopIt != jpopulation.end())
	{
		population.insertOne(parseJsonToIndividuum(*jpopIt));
		jpopIt++;
	}
}