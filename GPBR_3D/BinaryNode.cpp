#include "BinaryNode.h"

//BinaryNode::BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right):
//    func(func),
//    IExpressionNode(node_name,std::move(left), std::move(right))
//{
//
//}

BinaryNode::BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode> left, std::unique_ptr<IExpressionNode> right):
    func(func),
    IExpressionNode(node_name, std::move(left), std::move(right))
{
}

BinaryNode::BinaryNode(const BinaryNode& node):
    IExpressionNode(node),
    func(node.func)
{
}

arma::dmat BinaryNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
    return func(left->evaluate(thetha, phi), right->evaluate(thetha, phi));
}

std::string BinaryNode::toString() const
{
    return std::format("({} {} {})", left->toString(), node_name, right->toString());
}

std::unique_ptr<IExpressionNode> BinaryNode::clone()
{
    return std::make_unique<BinaryNode>(*this);
}
