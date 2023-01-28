#include "NodeReplaceMutation.h"

NodeReplaceMutation::NodeReplaceMutation(std::shared_ptr<TreeGenerator> tree_gen, double prob):
	GeneticOpretator(prob),
	tree_gen(tree_gen)
{
}

void NodeReplaceMutation::apply(std::weak_ptr<Individuum> individuum)
{
	auto& tree = individuum.lock()->getTree();
	// If tree has only one node(root) generate new tree.
	if (tree->getHeight() == 0)
		return;

	uint rand_ = Random::get({ 1, 2, 3 });
	if (rand_ == 1)
	{
		std::vector<uint> leafs_list = tree->filterNodesIdexes(std::make_unique< NodeReplaceMutation::LeafFilter>());
		uint rand_leaf = *Random::get(leafs_list.begin(), leafs_list.end());
	}
	else if (rand_ == 2)
	{
		std::vector<uint> unary_list = tree->filterNodesIdexes(std::make_unique< NodeReplaceMutation::UnaryFilter>());
		uint rand_unary = *Random::get(unary_list.begin(), unary_list.end());
	}
	else
	{
		std::vector<uint> binary_list = tree->filterNodesIdexes(std::make_unique< NodeReplaceMutation::BinaryFilter>());
		uint rand_binary = *Random::get(binary_list.begin(), binary_list.end());
	}

	//std::unique_ptr<Tree::NodeFilter> not_root_filter = std::make_unique<NodeNotRootFilter>();

	//auto nodes = tree->GetNodesPosWithFilter(not_root_filter);
	//int rand_node = *Random::get(nodes.begin(), nodes.end());

	//auto& old_node = tree->GetNodeRefAtPos(rand_node);

	//if (tree->GetHeight() == 0)
	//	return;

	//if (old_node->IsLeaf()) // terminal
	//{
	//	auto new_node = node_gen->RandTerminal();
	//	tree->SwapNodeToAtPos(new_node, rand_node);
	//	return;
	//}

	//if (old_node->GetRightSon() == nullptr) // unary function
	//{
	//	auto new_node = node_gen->RandUnaryFunctional();
	//	auto new_left = old_node->GetLeftSon()->clone();
	//	new_node->SetLeftSon(new_left);
	//	tree->SwapNodeToAtPos(new_node, rand_node);
	//	return;
	//}

	//auto new_node = node_gen->RandBinaryFunctional();
	//auto new_left = old_node->GetLeftSon()->clone();
	//auto new_right = old_node->GetRightSon()->clone();
	//new_node->SetLeftSon(new_left);
	//new_node->SetRightSon(new_right);
	//tree->SwapNodeToAtPos(new_node, rand_node);
}
bool NodeReplaceMutation::LeafFilter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return IsLeaf()(node);
}

bool NodeReplaceMutation::UnaryFilter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return IsUnary()(node);
}

bool NodeReplaceMutation::BinaryFilter::selectCondition(const std::unique_ptr<IExpressionNode>& node)
{
	return IsBinary()(node);
}
