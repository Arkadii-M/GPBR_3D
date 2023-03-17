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

TreeDerivative VariableNode::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivative::PartialDerivativeStrategy strategy)
{
    auto eval = evaluate(thetha, phi);
    switch (strategy)
    {
    case TreeDerivative::PartialDerivativeStrategy::OnlyConstsDerivative:
        return TreeDerivative(eval);
    default:
        break;
    }
    throw std::logic_error("autoDiffReverse invalid strategy");

    //if (strategy == TreeDerivative::PartialDerivativeStrategy::OnlyConstsDerivative)
    //    return TreeDerivative(
    //        eval,
    //        TreeDerivative::LeafDerivative(
    //            this->order_number,
    //            arma::dmat(thetha.n_rows, thetha.n_cols, arma::fill::ones)));

    //return TreeDerivative(
    //    eval,
    //    TreeDerivative::LeafDerivative(
    //        this->order_number,
    //        arma::dmat(thetha.n_rows, thetha.n_cols, arma::fill::zeros)));
    //auto eval = evaluate(thetha, phi);
    //if (dinfo.inDiffIdArray(this->order_number))
    //{
    //    auto ones = arma::dcube(thetha.n_rows, thetha.n_cols, dinfo.getNelements(), arma::fill::ones);
    //    return TreeDerivative(eval, ones);
    //}
    //auto zeros = arma::dcube(thetha.n_rows, thetha.n_cols, dinfo.getNelements(), arma::fill::zeros);
    //return TreeDerivative(eval, zeros);
}


std::any VariableNode::getValue() const
{
    return this->node_name;
}
