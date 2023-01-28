#pragma once
#ifndef NODE_H
#define NODE_H
#include <variant>
#include <string>
#include <memory>

class INode
{
protected:
	std::unique_ptr<INode> left, right;

public:
	INode();

	bool IsLeaf() const;

	std::unique_ptr<INode>& GetLeftSon();
	std::unique_ptr<INode>& GetRightSon();

	void SetLeftSon(std::unique_ptr<INode>& rhs);
	void SetRightSon(std::unique_ptr<INode>& rhs);

	virtual std::string ToString() const = 0;
};

#endif //NODE_H