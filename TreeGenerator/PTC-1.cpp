#include "PTC-1.h"

PTC_1_Generator::PTC_1_Generator(std::shared_ptr<GpData>& dat, uint expect_size, uint max_h):
    TreeGenerator(dat),
    expect_size(expect_size),
    max_h(max_h)
{
    auto bset = data->getBinaryFunction();
    auto uset = data->getUnaryFunction();

    uint b_size = bset.size();
    uint u_size = uset.size();

    double sum = 0;
    for (auto& bitem : bset)
        sum += bitem.getProbability();

    sum *= 2;
    for (auto& uitem : uset)
        sum += uitem.getProbability();

    this->prob_p = (1.0 - (1.0 / expect_size)) / sum;
}


std::unique_ptr<ExpressionTree> PTC_1_Generator::generateTree()
{
    return std::make_unique<ExpressionTree>(ptc1Alg(max_h));
}

std::unique_ptr<ExpressionTree> PTC_1_Generator::generateTree(uint h)
{
    return std::make_unique<ExpressionTree>(ptc1Alg(h));
}

std::unique_ptr<ExpressionTree> PTC_1_Generator::generateTree(uint max_h, uint min_h)
{
    return generateTree(Random::get(min_h,max_h));
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::generateSubTree()
{
    return ptc1Alg(max_h);
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::generateSubTree(uint h)
{
    return ptc1Alg(h);
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::generateSubTree(uint max_h, uint min_h)
{
    return ptc1Alg(Random::get(min_h, max_h));
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::ptc1Alg(uint ltc)
{
    if (ltc == 0)
        return createTerminal(ltc);

    //if (Random::get<double>(0.0, 1.0) < prob_p)
    //    return createFunctional(ltc);

    if (Random::get<double>(0.0, 1.0) > prob_p)//TODO: check
        return createFunctional(ltc);

    return createTerminal(ltc);
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::createTerminal(uint ltc)
{
    return generateTerminal();
}

std::unique_ptr<IExpressionNode> PTC_1_Generator::createFunctional(uint ltc)
{
    if (Random::get<bool>()) // Create unary
    {
        auto unary = generateUnary();
        unary->setLeftSon(ptc1Alg(ltc - 1));
        return unary;
    }
    auto binary = generateBinary();
    binary->setLeftSon(ptc1Alg(ltc - 1));
    binary->setRightSon(ptc1Alg(ltc - 1));
    return binary;
}
