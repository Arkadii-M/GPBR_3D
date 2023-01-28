#pragma once
#ifndef GP_PARSER_H
#define GP_PARSER_H


#include <memory>
#include <string>
#include "ExpressionTree.h"
#include "nlohmann/json.hpp"
#include "GpData.h"


#include "../GPBR_3D/BinaryNode.h"
#include "../GPBR_3D/UnaryNode.h"
#include "../GPBR_3D/VariableNode.h"
#include "../GPBR_3D/ConstantNode.h"
#include "Population.h"
#include "Individuum.h"

using json = nlohmann::json;

class GpParser {
private:
	std::shared_ptr<GpData> data;

public:
	GpParser(std::shared_ptr<GpData> data);

	// Tree
	json parseTreeToJson(std::unique_ptr<ExpressionTree>& tree);
	std::unique_ptr<ExpressionTree> parseJsonToTree(json tree);

	// Individuum
	json parseIndividuumToJson(std::weak_ptr<Individuum> individuum);
	std::shared_ptr<Individuum> parseJsonToIndividuum(json individuum);

	// Population
	json parsePopulationToJson(Population & population);
	void parseJsonToPopulation(json jpopulation, Population& population);
private:
	// Tree
	json parseSubTreeToJson(std::unique_ptr<IExpressionNode>& node);
	std::unique_ptr<IExpressionNode> parseJsonToSubTree(json subtree);

};

#endif // !GP_PARSER_H
