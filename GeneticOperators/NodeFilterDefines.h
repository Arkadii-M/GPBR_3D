#pragma once
#include "../GP/ExpressionTree.h"
#ifndef TREE_NODE_FILTER_DEFINES_H
#define TREE_NODE_FILTER_DEFINES_H

struct NotRoot
{
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->getDepth() != 0;
	}
};

struct MinHeight
{
	uint min_h;
	MinHeight(uint min_h):min_h(min_h) {}
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->getHeight() >= min_h;
	}
};

struct IsLeaf
{
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->isLeaf();
	}
};

struct IsUnary
{
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->isUnary();
	}
};

struct IsBinary
{
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->isBinary();
	}
};

struct IsNumber
{
	bool operator()(const std::unique_ptr<NodeObserver>& node)
	{
		return node->isConstant();
	}
};



#endif // TREE_NODE_FILTER_DEFINES_H