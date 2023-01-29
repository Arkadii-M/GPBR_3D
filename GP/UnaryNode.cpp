#include "UnaryNode.h"

//UnaryNode::UnaryNode(dmatUnaryFunc func,std::string node_name, std::unique_ptr<IExpressionNode>& left):
//	func(func),
//	IExpressionNode(node_name,std::move(left))
//{
//}

UnaryNode::UnaryNode(dmatUnaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode> left):
	func(func),
	IExpressionNode(node_name, std::move(left))
{
}

UnaryNode::UnaryNode(const UnaryNode& node):
	IExpressionNode(node),
	func(node.func)
{
}

arma::dmat UnaryNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
	return func(left->evaluate(thetha,phi));
}

std::string UnaryNode::toString() const
{
	return std::format("{}({})", node_name, left->toString());
}

std::unique_ptr<IExpressionNode> UnaryNode::clone()
{
	return std::make_unique<UnaryNode>(*this);
}
