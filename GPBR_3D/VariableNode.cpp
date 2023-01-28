#include "VariableNode.h"
VariableNode::VariableNode(std::string node_name):
    IExpressionNode(node_name)
{
    if (node_name != "thetha" && node_name != "phi")
    {
        throw std::logic_error("Only thetha or phi variable are supported");
    }
}
VariableNode::VariableNode(const VariableNode& node):
    IExpressionNode(node)
{
}
arma::dmat VariableNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
{
    if (node_name == "thetha")
        return thetha;
    else if(node_name == "phi")
        return phi;
}

std::string VariableNode::toString() const
{
    return node_name;
}

std::unique_ptr<IExpressionNode> VariableNode::clone()
{
    return std::make_unique<VariableNode>(*this);
}
