#include "ConstantNode.h"

//ConstantNode::ConstantNode(double value, arma::uword n_row, arma::uword n_col):
//    ConstMatrix(arma::dmat(n_row, n_col, arma::fill::value(value))),
//    value(value),
//    IExpressionNode(std::format("{:.5f}", value))
//{
//    
//}
ConstantNode::ConstantNode(double value):
    value(value),
    IExpressionNode(std::format("{:.5f}", value))
{

}

//ConstantNode::ConstantNode(const ConstantNode& node):
//    IExpressionNode(node),
//    value(node.value),
//    ConstMatrix(node.ConstMatrix)
//{
//}
ConstantNode::ConstantNode(const ConstantNode& node) :
    IExpressionNode(node),
    value(node.value)
{
}

arma::dmat ConstantNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
    return arma::dmat(thetha.n_rows,thetha.n_cols, arma::fill::value(value));
}

std::string ConstantNode::toString() const
{
    return std::format("{:.5f}",value);
}

std::unique_ptr<IExpressionNode> ConstantNode::clone()
{
    return std::make_unique<ConstantNode>(*this);
}
