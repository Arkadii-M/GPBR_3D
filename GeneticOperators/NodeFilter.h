#pragma once
#include "../GP/ExpressionTree.h"
#ifndef TREE_NODE_FILTER_H
#define TREE_NODE_FILTER_H

//struct NotRoot : public ExpressionTree::NodeFilter
//{
//	virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override {
//		return node->getNum() != 1;
//	}
//};

struct NotRoot
{
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		return node->getDepth() != 0;;
	}
	//virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override {
	//	return node->getNum() != 1;
	//}
};

struct MinHeight
{
	uint min_h;
	MinHeight(uint min_h):min_h(min_h) {}
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		return node->getHeight() >= min_h;
	}
};

struct IsLeaf
{
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		return node->isLeaf();
	}
};

struct IsUnary
{
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		return !node->isLeaf() && node->getRightSon();
	}
};

struct IsBinary
{
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		return node->getLeftSon() && node->getRightSon();
	}
};

struct IsNumber
{
	//inline bool isNumber(const std::string& s) {
	//	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
	//}

	//bool operator()(const std::unique_ptr<IExpressionNode>& node)
	//{
	//	return isNumber(node->getName());
	//}
	bool operator()(const std::unique_ptr<IExpressionNode>& node)
	{
		// TODO: CNAGE
		try
		{
			std::stod(node->getName());
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
};



#endif // TREE_NODE_FILTER_H