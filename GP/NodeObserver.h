#pragma once
#ifndef NODE_OBSERVER_H
#define NODE_OBSERVER_H
#include <memory>
#include "IExpressionNode.h"


class NodeObserver {
private:
	std::unique_ptr<IExpressionNode>& current;
public:
	NodeObserver() = default;
	NodeObserver(std::unique_ptr<IExpressionNode>& curr);
	NodeObserver(const std::unique_ptr<NodeObserver>& rhs);
	~NodeObserver() = default;

	std::unique_ptr<NodeObserver> getLeft() const;
	std::unique_ptr<NodeObserver> getRight() const;
	bool isLeaf() const;
	bool isVariable() const;
	bool isConstant() const;
	bool isUnary() const;
	bool isBinary() const;
	bool isNull() const;
	std::any getValue() const;

	std::string getName() const;
	uint getNum() const;
	uint getHeight() const;
	uint getDepth() const;
	std::string print() const;

	std::unique_ptr<IExpressionNode> subTreeCopy();
	static void SwapSubTrees(std::unique_ptr<NodeObserver>& first, std::unique_ptr<NodeObserver>& second);
	static void SwapSubTrees(std::unique_ptr<NodeObserver>& first, std::unique_ptr<IExpressionNode> second);
	static void ReplaceNodes(std::unique_ptr<NodeObserver>& first, std::unique_ptr<NodeObserver>& second);
	static void ReplaceNodes(std::unique_ptr<NodeObserver>& first, std::unique_ptr<IExpressionNode> second);
};



#endif // !NODE_OBSERVER_H
