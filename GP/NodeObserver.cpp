#include "NodeObserver.h"

NodeObserver::NodeObserver(std::unique_ptr<IExpressionNode>& curr) :
	current(curr)
{
}
NodeObserver::NodeObserver(const std::unique_ptr<NodeObserver> & rhs):
	current(rhs->current)
{
}

std::unique_ptr<NodeObserver> NodeObserver::getLeft() const
{
	return std::make_unique<NodeObserver>(current->getLeftSon());
}

std::unique_ptr<NodeObserver> NodeObserver::getRight() const
{
	return std::make_unique<NodeObserver>(current->getRightSon());
}

bool NodeObserver::isLeaf() const
{
	return current->isLeaf();
}

bool NodeObserver::isVariable() const
{
	auto name = current->getName();
	return name == "thetha" || name == "phi";//TODO: CHANGE
}

bool NodeObserver::isConstant() const
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

bool NodeObserver::isUnary() const
{
	return current->getLeftSon() && !current->getRightSon();
}

bool NodeObserver::isBinary() const
{
	return current->getLeftSon() && current->getRightSon();
}

bool NodeObserver::isNull() const
{
	return false;
}

std::any NodeObserver::getValue() const
{
	return current->getValue();
}

std::string NodeObserver::getName() const
{
	return current->getName();
}

uint NodeObserver::getNum() const
{
	return current->getNum();
}

uint NodeObserver::getHeight() const
{
	return current->getHeight();
}

uint NodeObserver::getDepth() const
{
	return current->getDepth();
}

std::string NodeObserver::print() const
{
	return current->toString();
}

std::unique_ptr<IExpressionNode> NodeObserver::subTreeCopy()
{
	return current->clone();
}

void NodeObserver::SwapSubTrees(std::unique_ptr<NodeObserver>& first, std::unique_ptr<NodeObserver>& second)
{
	first->current.swap(second->current);
}

void NodeObserver::SwapSubTrees(std::unique_ptr<NodeObserver>& first, std::unique_ptr<IExpressionNode> second)
{
	first->current.swap(second);
}

void NodeObserver::ReplaceNodes(std::unique_ptr<NodeObserver>& first, std::unique_ptr<NodeObserver>& second)
{
	// Swap childs
	first->current->getLeftSon().swap(second->current->getLeftSon());
	first->current->getRightSon().swap(second->current->getRightSon());
	// Swap nodes
	first->current.swap(second->current);
}

void NodeObserver::ReplaceNodes(std::unique_ptr<NodeObserver>& first, std::unique_ptr<IExpressionNode> second)
{
	// Swap childs
	first->current->getLeftSon().swap(second->getLeftSon());
	first->current->getRightSon().swap(second->getRightSon());
	// Swap nodes
	first->current.swap(second);
}
