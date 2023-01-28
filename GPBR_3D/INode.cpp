#include "INode.h"

INode::INode()
{
	left.release();
	right.release();
}

bool INode::IsLeaf() const
{
	return !(left || right);
}

std::unique_ptr<INode>& INode::GetLeftSon()
{
	return left;
}

std::unique_ptr<INode>& INode::GetRightSon()
{
	return right;
}

void INode::SetLeftSon(std::unique_ptr<INode>& rhs)
{
	left = std::move(rhs);
}

void INode::SetRightSon(std::unique_ptr<INode>& rhs)
{
	right = std::move(rhs);
}
