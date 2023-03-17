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
std::vector<uint> ExpressionTree::filterNodes(NodeFilter filter)
{
	TreeTraversal::preOrder(getRootObserver(), filter);
	return filter.getFilteredIndexes();
}

arma::dmat ExpressionTree::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
	return root->evaluate(thetha,phi);
}

//TreeDerivative ExpressionTree::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo)
//{
//	return root->autoDiffReverse(thetha, phi, dinfo);
//}

TreeDerivative ExpressionTree::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivative::PartialDerivativeStrategy strategy)
{
	return root->autoDiffReverse(thetha, phi, strategy);
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

void ExpressionTree::SwapSubTress(std::unique_ptr<ExpressionTree>& first_tree, std::unique_ptr<ExpressionTree>& second_tree, std::unique_ptr<NodeObserver>& first_observe, std::unique_ptr<NodeObserver>& second_observe)
{
	NodeObserver::SwapSubTrees(first_observe, second_observe);
	first_tree->recalculate();
	second_tree->recalculate();
}
void ExpressionTree::ReplaceNodes(
	std::unique_ptr<ExpressionTree>& first_tree,
	std::unique_ptr<ExpressionTree>& second_tree,
	std::unique_ptr<NodeObserver>& first_observe,
	std::unique_ptr<NodeObserver>& second_observe)
{
	NodeObserver::ReplaceNodes(first_observe, second_observe);
	first_tree->recalculate();
	second_tree->recalculate();
}

std::unique_ptr<NodeObserver> ExpressionTree::getRootObserver()
{
	return std::make_unique<NodeObserver>(root);
}
std::unique_ptr<NodeObserver> ExpressionTree::getNodeObserver(uint node_id)
{
	std::unique_ptr<ExpressionTree::OrderHandler> handler = std::make_unique<ExpressionTree::ObserverExtract>(node_id);
	preOrder(root, handler);
	return static_cast<ObserverExtract*>(handler.get())->getObserver();
}

ExpressionTree::ObserverExtract::ObserverExtract(uint id):
	node_id(id),
	observer(nullptr)
{
}

std::unique_ptr <NodeObserver> ExpressionTree::ObserverExtract::getObserver()
{
	return std::move(observer);
}

bool ExpressionTree::ObserverExtract::operator()(std::unique_ptr<IExpressionNode>& node)
{
	if (node->getNum() == node_id)
	{
		observer = std::make_unique<NodeObserver>(node);
		return true;
	}
	return false;
}