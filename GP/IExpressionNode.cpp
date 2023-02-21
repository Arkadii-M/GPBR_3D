#include "IExpressionNode.h"

IExpressionNode::IExpressionNode(std::string node_name):
	node_name(node_name),
	order_number(0),
	height(0),
	depth(0)
{
	left.release();
	right.release();
}

//IExpressionNode::IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode>& left) :
//	node_name(node_name),
//	left(std::move(left)),
//	order_number(0),
//	height(0),
//	depth(0)
//{
//	left.release();
//}
//
//IExpressionNode::IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right) :
//	node_name(node_name),
//	left(std::move(left)),
//	right(std::move(right)),
//	order_number(0),
//	height(0),
//	depth(0)
//{
//}

IExpressionNode::IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode> left):
	node_name(node_name),
	left(std::move(left)),
	order_number(0),
	height(0),
	depth(0)
{
	right.release();
}

IExpressionNode::IExpressionNode(std::string node_name, std::unique_ptr<IExpressionNode> left, std::unique_ptr<IExpressionNode> right):
	node_name(node_name),
	left(std::move(left)),
	right(std::move(right)),
	order_number(0),
	height(0),
	depth(0)
{
}

IExpressionNode::IExpressionNode(const IExpressionNode& node):
	node_name(node.node_name),
	order_number(node.order_number),
	height(node.height),
	depth(node.depth)
{
	if (node.left)
		left = std::move(node.left->clone());
	else
		left.release();

	if (node.right)
		right = std::move(node.right->clone());
	else
		right.release();
}

IExpressionNode::IExpressionNode(const std::unique_ptr<IExpressionNode>& node):
	node_name(node->node_name),
	order_number(node->order_number),
	height(node->height),
	depth(node->depth)
{
	if (node->left)
		left = std::move(node->left->clone());
	else
		left.release();

	if (node->right)
		right = std::move(node->right->clone());
	else
		right.release();
}

bool IExpressionNode::isLeaf() const
{
	return !(left || right);
}

uint IExpressionNode::getNum() const
{
	return order_number;
}

void IExpressionNode::setNum(uint num)
{
	order_number = num;
}

uint IExpressionNode::getDepth() const
{
	return depth;
}

void IExpressionNode::setDepth(uint depth)
{
	this->depth = depth;
}

uint IExpressionNode::getHeight() const
{
	return height;
}

void IExpressionNode::setHeight(uint h)
{
	height = h;
}

std::unique_ptr<IExpressionNode>& IExpressionNode::getLeftSon()
{
	return left;
}

std::unique_ptr<IExpressionNode>& IExpressionNode::getRightSon()
{
	return right;
}

void IExpressionNode::setLeftSon(std::unique_ptr<IExpressionNode> rhs)
{
	left = std::move(rhs);
}

void IExpressionNode::setRightSon(std::unique_ptr<IExpressionNode> rhs)
{
	right = std::move(rhs);
}

bool IExpressionNode::Equal(const IExpressionNode& first, const IExpressionNode& second)
{
	return
		first.height == second.height &&
		first.depth == second.depth &&
		first.order_number == second.order_number &&
		first.toString() == second.toString();

	//TODO: check if fast check is enough
	//if (!fast)
	//	return false;

	//if (first.left != nullptr)
	//	if (!INode::Equal(*first.left.get(), *second.left.get()))
	//		return false;


	//if (first.right != nullptr)
	//	if (!INode::Equal(*first.right.get(), *second.right.get()))
	//		return false;

	//return true;
}
std::string IExpressionNode::getName() const
{
	return node_name;
}

std::ostream& operator<<(std::ostream& os, const std::unique_ptr<IExpressionNode>& node)
{
	os << std::format("name: {} \tnumber: {} \theight: {} \tdepth: {}",
		node->node_name,
		node->order_number,
		node->height,
		node->depth);
	return os;
}
