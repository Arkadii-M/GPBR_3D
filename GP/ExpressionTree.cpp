//#include "ExpressionTree.h"
//
//ExpressionTree::ExpressionTree(std::unique_ptr<IExpressionNode> root) :
//	total_nodes(0),
//	root(std::move(root))
//{
//	//this->root = std::move(root);
//	recalculate();
//}
//
//ExpressionTree::ExpressionTree(const ExpressionTree& tree) :
//	total_nodes(tree.total_nodes)
//{
//	root = std::move(tree.root->clone());
//}
//
//std::unique_ptr<IExpressionNode>& ExpressionTree::getRoot()
//{
//	return root;
//}
//
//void ExpressionTree::enumerateNodes()
//{
//	std::unique_ptr<OrderHandler> handler = std::make_unique<EnumerateHandler>();
//	preOrder(root, handler);
//	total_nodes = static_cast<EnumerateHandler*>(handler.get())->getTotalNodes();
//}
//
//uint ExpressionTree::getTotalNodes() const
//{
//	return total_nodes;
//}
//
//uint ExpressionTree::getHeight() const
//{
//	return root->getHeight();
//}
//
//void ExpressionTree::recalculate()
//{
//	enumerateNodes();
//	std::unique_ptr<OrderHandler> handler = std::make_unique<HeightHandler>();
//	postOrder(root, handler);
//}
//
//std::string ExpressionTree::print()
//{
//	return root->toString();
//}
//
//std::unique_ptr<IExpressionNode> ExpressionTree::SubTree(std::unique_ptr<ExpressionTree>& tree, const uint sub_index)
//{
//	std::unique_ptr<OrderHandler> subtree = std::make_unique<ExtractSubTree>(sub_index);// Swap subtree with temp node
//	tree->preOrder(tree->getRoot(), subtree);
//	return static_cast<ExtractSubTree*>(subtree.get())->getResult();
//}
//
//void ExpressionTree::ReplaceNode(std::unique_ptr<ExpressionTree>& tree, const uint index, std::unique_ptr<IExpressionNode> to_replace)
//{
//	//std::unique_ptr<OrderHandler> replace = std::make_unique<ReplaceNode>(index,std::move(to_replace));// Swap subtree with temp node
//	//std::make_unique<ReplaceNode>()
//}
//
//bool ExpressionTree::Equal(const ExpressionTree& first, const ExpressionTree& second)
//{
//	return
//		(first.total_nodes == second.total_nodes) &&
//		first.getHeight() == second.getHeight() &&
//		IExpressionNode::Equal(*first.root.get(), *second.root.get());
//}
//void ExpressionTree::SwapNodesAtPositions(std::unique_ptr<ExpressionTree>& first_tree, std::unique_ptr<ExpressionTree>& second_tree, const uint first_node_pos, const uint second_node_pos)
//{
//	std::unique_ptr<IExpressionNode> temp = std::make_unique<TempNode>(); // create temp node
//	std::unique_ptr<OrderHandler> first_index_swap = std::make_unique<SwapByIndexHandler>(first_node_pos, temp);// Swap temp and first node. Now first tree contains temp node.
//	first_tree->preOrder(first_tree->getRoot(), first_index_swap);
//
//	std::unique_ptr<OrderHandler> second_index_swap = std::make_unique<SwapByIndexHandler>(second_node_pos, temp); // Now temp contains second tree node
//	second_tree->preOrder(second_tree->getRoot(), second_index_swap);
//
//	std::unique_ptr<OrderHandler> first_temp_swap = std::make_unique<SwapTempHandler>(temp);
//	first_tree->preOrder(first_tree->getRoot(), first_temp_swap);
//
//	first_tree->recalculate();
//	second_tree->recalculate();
//}
//
//bool ExpressionTree::inOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
//{
//	if (!node)
//	{
//		handler->onEmpty();
//		return false;
//	}
//	handler->onVisitLeft();
//	if (inOrder(node->getLeftSon(), handler))
//		return true;
//
//	if (handler->operator()(node))
//		return true;
//
//	handler->onVisitRight();
//	if (inOrder(node->getRightSon(), handler))
//		return true;
//
//	handler->onReturn();
//	return false;
//}
//
//bool ExpressionTree::preOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
//{
//	if (!node)
//	{
//		handler->onEmpty();
//		return false;
//	}
//
//	if (handler->operator()(node))
//		return true;
//
//	handler->onVisitLeft();
//	if (preOrder(node->getLeftSon(), handler))
//		return true;
//
//	handler->onVisitRight();
//	if (preOrder(node->getRightSon(), handler))
//		return true;
//
//	handler->onReturn();
//	return false;
//}
//
//bool ExpressionTree::postOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
//{
//	if (!node)
//	{
//		handler->onEmpty();
//		return false;
//	}
//	handler->onVisitLeft();
//	if (postOrder(node->getLeftSon(), handler))
//		return true;
//
//	handler->onVisitRight();
//	if (postOrder(node->getRightSon(), handler))
//		return true;
//
//	if (handler->operator()(node))
//		return true;
//
//	handler->onReturn();
//	return false;
//}
//
//std::vector<uint> ExpressionTree::filterNodesIdexes(std::unique_ptr<NodeFilter> filter)
//{
//	std::unique_ptr<OrderHandler> node_filter = std::move(filter);
//	preOrder(root, node_filter);
//	return static_cast<NodeFilter*>(node_filter.get())->getResult();
//}
//
//// Enumerate implementation
//void ExpressionTree::EnumerateHandler::onVisitLeft() { curr_d++; }// go to the next level
//void ExpressionTree::EnumerateHandler::onVisitRight() { curr_d++; }// go to the next level
//void ExpressionTree::EnumerateHandler::onEmpty() { curr_d--; }// return to the top level
//void ExpressionTree::EnumerateHandler::onReturn() { curr_d--; }// return to the top level
//
//uint ExpressionTree::EnumerateHandler::getTotalNodes() const { return total_nodes; }
//bool ExpressionTree::EnumerateHandler::operator()(std::unique_ptr<IExpressionNode>& node) {
//	node->setNum(num++);
//	node->setDepth(curr_d);
//	total_nodes++;
//	return false;
//}
//
//// Height implementation
//bool ExpressionTree::HeightHandler::operator()(std::unique_ptr<IExpressionNode>& node) {
//	if (node->isLeaf())
//		node->setHeight(0);
//	else if (!node->getRightSon())
//	{
//		node->setHeight(node->getLeftSon()->getHeight() + 1);
//	}
//	else
//	{
//		node->setHeight(std::max(node->getLeftSon()->getHeight(), node->getRightSon()->getHeight()) + 1);
//	}
//	return false;
//
//}
//
//// Swap
//
//ExpressionTree::SwapByIndexHandler::SwapByIndexHandler(uint index, std::unique_ptr<IExpressionNode>& to_set) :
//	find_index(index),
//	find_node(to_set)
//{
//}
//
//bool ExpressionTree::SwapByIndexHandler::operator()(std::unique_ptr<IExpressionNode>& node)
//{
//	if (node->getNum() == find_index)
//	{
//		find_node.swap(node);
//		return true;
//	}
//	return false;
//}
//ExpressionTree::SwapTempHandler::SwapTempHandler(std::unique_ptr<IExpressionNode>& to_set) :
//	find_node(to_set)
//{
//}
//
//bool ExpressionTree::SwapTempHandler::operator()(std::unique_ptr<IExpressionNode>& node)
//{
//	if (node->getName() == "temp")
//	{
//		find_node.swap(node);
//		return true;
//	}
//	return false;
//}
//
//// Filter
//ExpressionTree::NodeFilter::NodeFilter()
//{
//	filtered_indexes = std::vector<uint>();
//}
//
//std::vector<uint> ExpressionTree::NodeFilter::getResult()
//{
//	return filtered_indexes;
//}
//bool ExpressionTree::NodeFilter::operator()(std::unique_ptr<IExpressionNode>& node)
//{
//	if (selectCondition(node))
//		filtered_indexes.push_back(node->getNum());
//	return false;
//}
//
//ExpressionTree::ExtractSubTree::ExtractSubTree(uint index) :
//	index(index)
//{
//	sub_tree.release();
//}
//std::unique_ptr<IExpressionNode> ExpressionTree::ExtractSubTree::getResult()
//{
//	return std::move(sub_tree);
//}
//bool ExpressionTree::ExtractSubTree::operator()(std::unique_ptr<IExpressionNode>& node)
//{
//	if (node->getNum() == index)
//	{
//		sub_tree = node->clone();
//		return true;
//	}
//	return false;
//}
//
//ExpressionTree::ReplaceNode::ReplaceNode(uint index, std::unique_ptr<IExpressionNode> to_replace):
//	index(index)
//{
//	to_replace = std::move(to_replace);
//}
//
//bool ExpressionTree::ReplaceNode::operator()(std::unique_ptr<IExpressionNode>& node)
//{
//	if (node->getNum() == index)
//	{
//		to_replace->setNum(node->getNum());
//		to_replace->setLeftSon(node->getLeftSon());
//		to_replace->setRightSon(node->getRightSon());
//		to_replace.swap(node);
//		return true;
//	}
//	return false;
//}
//
//ExpressionTree::NodeObserve::NodeObserve(std::unique_ptr<IExpressionNode>& curr):
//	current(curr)
//{
//}
//
//ExpressionTree::NodeObserve ExpressionTree::NodeObserve::getLeft() const
//{
//	return NodeObserve(current->getLeftSon());
//}
//
//ExpressionTree::NodeObserve ExpressionTree::NodeObserve::getRight() const
//{
//	return NodeObserve(current->getRightSon());
//}
//
//bool ExpressionTree::NodeObserve::isLeaf() const
//{
//	return current->isLeaf();
//}
//
//bool ExpressionTree::NodeObserve::isUnary() const
//{
//	return current->getLeftSon() && !current->getRightSon();
//}
//
//bool ExpressionTree::NodeObserve::isBinary() const
//{
//	return current->getLeftSon() && current->getRightSon();
//}
//
//std::string ExpressionTree::NodeObserve::getName() const
//{
//	return current->getName();
//}
//
//uint ExpressionTree::NodeObserve::getNum() const
//{
//	return current->getNum();
//}
//
//std::string ExpressionTree::NodeObserve::print() const
//{
//	return current->toString();
//}
//
//void ExpressionTree::NodeObserve::SwapSubTrees(NodeObserve& first, NodeObserve& second)
//{
//	first.current.swap(second.current);
//}
//
//void ExpressionTree::NodeObserve::ReplaceNodes(NodeObserve& first, NodeObserve& second)
//{
//	// Swap childs
//	first.current->getLeftSon().swap(second.current->getLeftSon());
//	first.current->getRightSon().swap(second.current->getRightSon());
//	// Swap nodes
//	first.current.swap(second.current);
//}
//void ExpressionTree::SwapSubTress(std::unique_ptr<ExpressionTree>& first_tree, std::unique_ptr<ExpressionTree>& second_tree, NodeObserve& first_observe, NodeObserve& second_observe)
//{
//	NodeObserve::SwapSubTrees(first_observe, second_observe);
//	first_tree->recalculate();
//	second_tree->recalculate();
//}
//void ExpressionTree::ReplaceNodes(
//	std::unique_ptr<ExpressionTree>& first_tree,
//	std::unique_ptr<ExpressionTree>& second_tree,
//	NodeObserve& first_observe,
//	NodeObserve& second_observe)
//{
//	NodeObserve::ReplaceNodes(first_observe, second_observe);
//	first_tree->recalculate();
//	second_tree->recalculate();
//
//}
#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(std::unique_ptr<IExpressionNode> root) :
	total_nodes(0),
	root(std::move(root))
{
	recalculate();
}

ExpressionTree::ExpressionTree(const ExpressionTree& tree) :
	total_nodes(tree.total_nodes)
{
	root = std::move(tree.root->clone());
}

void ExpressionTree::enumerateNodes()
{
	std::unique_ptr<OrderHandler> handler = std::make_unique<EnumerateHandler>();
	preOrder(root, handler);
	total_nodes = static_cast<EnumerateHandler*>(handler.get())->getTotalNodes();
}

uint ExpressionTree::getTotalNodes() const
{
	return total_nodes;
}

uint ExpressionTree::getHeight() const
{
	return root->getHeight();
}

void ExpressionTree::recalculate()
{
	enumerateNodes();
	std::unique_ptr<OrderHandler> handler = std::make_unique<HeightHandler>();
	postOrder(root, handler);
}

std::string ExpressionTree::print()
{
	return root->toString();
}

bool ExpressionTree::inOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
{
	if (!node)
	{
		handler->onEmpty();
		return false;
	}
	handler->onVisitLeft();
	if (inOrder(node->getLeftSon(), handler))
		return true;

	if (handler->operator()(node))
		return true;

	handler->onVisitRight();
	if (inOrder(node->getRightSon(), handler))
		return true;

	handler->onReturn();
	return false;
}

bool ExpressionTree::preOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
{
	if (!node)
	{
		handler->onEmpty();
		return false;
	}

	if (handler->operator()(node))
		return true;

	handler->onVisitLeft();
	if (preOrder(node->getLeftSon(), handler))
		return true;

	handler->onVisitRight();
	if (preOrder(node->getRightSon(), handler))
		return true;

	handler->onReturn();
	return false;
}

bool ExpressionTree::postOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler)
{
	if (!node)
	{
		handler->onEmpty();
		return false;
	}
	handler->onVisitLeft();
	if (postOrder(node->getLeftSon(), handler))
		return true;

	handler->onVisitRight();
	if (postOrder(node->getRightSon(), handler))
		return true;

	if (handler->operator()(node))
		return true;

	handler->onReturn();
	return false;
}

std::vector<uint> ExpressionTree::filterNodesIdexes(std::unique_ptr<NodeFilter> filter)
{
	std::unique_ptr<OrderHandler> node_filter = std::move(filter);
	preOrder(root, node_filter);
	return static_cast<NodeFilter*>(node_filter.get())->getResult();
}

arma::dmat ExpressionTree::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
	return root->evaluate(thetha,phi);
}

// Enumerate implementation
void ExpressionTree::EnumerateHandler::onVisitLeft() { curr_d++; }// go to the next level
void ExpressionTree::EnumerateHandler::onVisitRight() { curr_d++; }// go to the next level
void ExpressionTree::EnumerateHandler::onEmpty() { curr_d--; }// return to the top level
void ExpressionTree::EnumerateHandler::onReturn() { curr_d--; }// return to the top level

uint ExpressionTree::EnumerateHandler::getTotalNodes() const { return total_nodes; }
bool ExpressionTree::EnumerateHandler::operator()(std::unique_ptr<IExpressionNode>& node) {
	node->setNum(num++);
	node->setDepth(curr_d);
	total_nodes++;
	return false;
}

// Height implementation
bool ExpressionTree::HeightHandler::operator()(std::unique_ptr<IExpressionNode>& node) {
	if (node->isLeaf())
		node->setHeight(0);
	else if (!node->getRightSon())
	{
		node->setHeight(node->getLeftSon()->getHeight() + 1);
	}
	else
	{
		node->setHeight(std::max(node->getLeftSon()->getHeight(), node->getRightSon()->getHeight()) + 1);
	}
	return false;

}

// Filter
ExpressionTree::NodeFilter::NodeFilter()
{
	filtered_indexes = std::vector<uint>();
}

std::vector<uint> ExpressionTree::NodeFilter::getResult()
{
	return filtered_indexes;
}
bool ExpressionTree::NodeFilter::operator()(std::unique_ptr<IExpressionNode>& node)
{
	if (selectCondition(node))
		filtered_indexes.push_back(node->getNum());
	return false;
}
ExpressionTree::NodeObserve::NodeObserve(std::unique_ptr<IExpressionNode>& curr) :
	current(curr)
{
}

std::unique_ptr <ExpressionTree::NodeObserve> ExpressionTree::NodeObserve::getLeft() const
{
	return std::make_unique<NodeObserve>(current->getLeftSon());
}

std::unique_ptr<ExpressionTree::NodeObserve> ExpressionTree::NodeObserve::getRight() const
{
	return std::make_unique<NodeObserve>(current->getRightSon());
}

bool ExpressionTree::NodeObserve::isLeaf() const
{
	return current->isLeaf();
}

bool ExpressionTree::NodeObserve::isVariable() const
{
	auto name = current->getName();
	return name == "thetha" || name == "phi";//TODO: CHANGE
}
bool ExpressionTree::NodeObserve::isConstant() const
{
	// TODO: CNAGE
	try
	{
		std::stod(current->getName());
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool ExpressionTree::NodeObserve::isUnary() const
{
	return current->getLeftSon() && !current->getRightSon();
}

bool ExpressionTree::NodeObserve::isBinary() const
{
	return current->getLeftSon() && current->getRightSon();
}
bool ExpressionTree::NodeObserve::isNull() const
{
	return !current;
}
std::string ExpressionTree::NodeObserve::getName() const
{
	return current->getName();
}

uint ExpressionTree::NodeObserve::getNum() const
{
	return current->getNum();
}

std::string ExpressionTree::NodeObserve::print() const
{
	return current->toString();
}

std::unique_ptr<IExpressionNode> ExpressionTree::NodeObserve::subTreeCopy()
{
	return current->clone();
}

void ExpressionTree::NodeObserve::SwapSubTrees(std::unique_ptr<NodeObserve>& first, std::unique_ptr<NodeObserve>& second)
{
	first->current.swap(second->current);
}

void ExpressionTree::NodeObserve::SwapSubTrees(std::unique_ptr<NodeObserve>& first, std::unique_ptr<IExpressionNode> second)
{
	first->current.swap(second);
}

void ExpressionTree::NodeObserve::ReplaceNodes(std::unique_ptr<NodeObserve>& first, std::unique_ptr<NodeObserve>& second)
{
	// Swap childs
	first->current->getLeftSon().swap(second->current->getLeftSon());
	first->current->getRightSon().swap(second->current->getRightSon());
	// Swap nodes
	first->current.swap(second->current);
}
void ExpressionTree::NodeObserve::ReplaceNodes(std::unique_ptr<NodeObserve>& first, std::unique_ptr<IExpressionNode> second)
{
	// Swap childs
	first->current->getLeftSon().swap(second->getLeftSon());
	first->current->getRightSon().swap(second->getRightSon());
	// Swap nodes
	first->current.swap(second);
}
void ExpressionTree::SwapSubTress(std::unique_ptr<ExpressionTree>& first_tree, std::unique_ptr<ExpressionTree>& second_tree, std::unique_ptr<NodeObserve>& first_observe, std::unique_ptr<NodeObserve>& second_observe)
{
	NodeObserve::SwapSubTrees(first_observe, second_observe);
	first_tree->recalculate();
	second_tree->recalculate();
}
void ExpressionTree::ReplaceNodes(
	std::unique_ptr<ExpressionTree>& first_tree,
	std::unique_ptr<ExpressionTree>& second_tree,
	std::unique_ptr<NodeObserve>& first_observe,
	std::unique_ptr<NodeObserve>& second_observe)
{
	NodeObserve::ReplaceNodes(first_observe, second_observe);
	first_tree->recalculate();
	second_tree->recalculate();
}

std::unique_ptr<ExpressionTree::NodeObserve> ExpressionTree::getRootObserver()
{
	return std::make_unique<NodeObserve>(root);
}

std::unique_ptr <ExpressionTree::NodeObserve> ExpressionTree::getNodeObserver(uint node_id)
{
	std::unique_ptr<OrderHandler> handler = std::make_unique<ObserverExtract>(node_id);
	preOrder(root, handler);
	return static_cast<ObserverExtract*>(handler.get())->getObserver();
}

ExpressionTree::ObserverExtract::ObserverExtract(uint id):
	node_id(id),
	observer(nullptr)
{
}

std::unique_ptr <ExpressionTree::NodeObserve> ExpressionTree::ObserverExtract::getObserver()
{
	return std::move(observer);
}

bool ExpressionTree::ObserverExtract::operator()(std::unique_ptr<IExpressionNode>& node)
{
	if (node->getNum() == node_id)
	{
		observer = std::make_unique<NodeObserve>(node);
		return true;
	}
	return false;
}
