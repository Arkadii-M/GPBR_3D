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

TreeDerivative BinaryNode::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivative::PartialDerivativeStrategy strategy)
{
    // Calculate values first
    auto left_res = left->autoDiffReverse(thetha, phi, strategy);
    auto right_res = left->autoDiffReverse(thetha, phi, strategy);


    return TreeDerivative(thetha);
    // Calculate derivatives
    //auto eval = func(left_res.getValues(), right_res.getValues());
    //auto der = dfunc(left_res.getValues(), right_res.getValues(), left_res.getDerivatives(), right_res.getDerivatives());
    //return TreeDerivative(eval, der);
}

std::any BinaryNode::getValue() const
{
    return func;
}
