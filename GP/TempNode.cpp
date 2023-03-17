//#include "TempNode.h"
//
//
//TempNode::TempNode() :
//    IExpressionNode("temp")
//{
//}
//
//
//arma::dmat TempNode::evaluate(const arma::dmat& thetha, const arma::dmat& phi)
//{
//    throw std::logic_error("Temp node can't be evaluated");
//}
//
//std::unique_ptr<IExpressionNode> TempNode::clone()
//{
//    throw std::logic_error("Temp node can't be cloned");
//}
//
//std::string TempNode::toString() const
//{
//    return "temp";
//}
//
//TreeDerivative TempNode::autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo)
//{
//    throw std::logic_error("Temp node can't be evaluated");
//}
//
//
//std::any TempNode::getValue() const
//{
//    return this->node_name;
//}
