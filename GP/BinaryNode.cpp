#include "BinaryNode.h"

//BinaryNode::BinaryNode(dmatBinaryFunc func, std::string node_name, std::unique_ptr<IExpressionNode>& left, std::unique_ptr<IExpressionNode>& right):
//    func(func),
//    IExpressionNode(node_name,std::move(left), std::move(right))
//{
//
//}

BinaryNode::BinaryNode(dmatBinaryFunc func,
    dmatBinaryDerivative dfunc,
    std::string node_name,
    std::unique_ptr<IExpressionNode> left,
    std::unique_ptr<IExpressionNode> right):
    IExpressionNode(node_name, std::move(left), std::move(right)),
    func(func),
    dfunc(dfunc)
{
}

BinaryNode::BinaryNode(const BinaryNode& node):
    IExpressionNode(node),
    func(node.func),
    dfunc(node.dfunc)
{
}

arma::dmat BinaryNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
    return func(left->evaluate(thetha, phi), right->evaluate(thetha, phi));
}

std::string BinaryNode::toString() const
{
    return std::format("({} .{} {})", left->toString(), node_name, right->toString());
}

std::unique_ptr<IExpressionNode> BinaryNode::clone()
{
    return std::make_unique<BinaryNode>(*this);
}

TreeDerivative BinaryNode::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo)
{
    // Calculate values first
    auto left_res = left->autoDiffReverse(thetha, phi, dinfo);
    auto right_res = left->autoDiffReverse(thetha, phi, dinfo);
    // Calculate derivatives
    auto eval = func(left_res.getElement(), right_res.getElement());
    auto der = dfunc(left_res.getElement(), right_res.getElement(), left_res.getDerivative(), right_res.getDerivative());
    return TreeDerivative(eval, der);
}
