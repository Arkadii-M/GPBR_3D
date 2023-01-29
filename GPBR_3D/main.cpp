#include <iostream>

#include "../GP/ExpressionTree.h"
#include "../GP/GpData.h"
#include "../GP/GpParser.h"
#include "../GP/TempNode.h"
//#include "../GP/GpParser.h"

struct RootFilter : public ExpressionTree::NodeFilter
{
	virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) override {
		return node->getNum() != 1;
	}
};

int main()
{
	std::unique_ptr<IExpressionNode> thetha = std::make_unique<VariableNode>("thetha");
	std::unique_ptr<IExpressionNode> phi = std::make_unique<VariableNode>("phi");

	std::unique_ptr<IExpressionNode> cos = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "cos", std::move(thetha));
	std::unique_ptr<IExpressionNode> sin = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "sin", std::move(phi));


	std::unique_ptr<IExpressionNode> plus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", std::move(cos), std::move(sin));


	std::unique_ptr<IExpressionNode> thetha1 = std::make_unique<VariableNode>("thetha");
	std::unique_ptr<IExpressionNode> phi1 = std::make_unique<VariableNode>("phi");

	std::unique_ptr<IExpressionNode> exp = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "exp", std::move(thetha1));
	std::unique_ptr<IExpressionNode> tan = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "tan", std::move(phi1));


	std::unique_ptr<IExpressionNode> minus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "-", std::move(exp), std::move(tan));

	std::unique_ptr<ExpressionTree> tree1 = std::make_unique<ExpressionTree>(std::move(plus));
	std::unique_ptr<ExpressionTree> tree2 = std::make_unique<ExpressionTree>(std::move(minus));

	std::cout << tree1->print() << "\n";
	std::cout << tree2->print() << "\n\n\n";

	auto t1_o = tree1->getRootObserver()->getLeft();
	auto t2_o = tree2->getRootObserver()->getRight();

	ExpressionTree::ReplaceNodes(tree1,tree2,t1_o, t2_o);


	std::cout << tree1->print() << "\n";
	std::cout << tree2->print() << "\n";
	//std::cout << t1_o.print() << "\n";
	//std::cout << t2_o.print() << "\n";

	//ExpressionTree::SwapNodesAtPositions(tree1, tree2, 2, 4);


	//std::cout << tree1->getRoot()->toString() << "\n";
	//std::cout << tree2->getRoot()->toString() << "\n";

	//std::unique_ptr<ExpressionTree::NodeFilter> root_filter = std::make_unique<RootFilter>();
	//auto ret_vec = tree1->filterNodesIdexes(root_filter);


	//const arma::uword n_repeat = 1;
	//GpData::Bset bset = GpData::Bset();
	//bset.insert(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", 1.0));
	//bset.insert(GpData::BinaryItem([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", 1.0));

	//GpData::Uset uset = GpData::Uset();
	//uset.insert(GpData::UnaryItem([](const arma::dmat& val) {return arma::cos(val); }, "cos", 1.0));
	//uset.insert(GpData::UnaryItem([](const arma::dmat& val) {return arma::sin(val); }, "sin", 1.0));

	//GpData::Vset vset = GpData::Vset();
	//vset.insert(GpData::VariableItem("thetha","thetha", 1.0));
	//vset.insert(GpData::VariableItem("phi", "phi", 1.0));

	//GpData::Cset cset = GpData::Cset();
	//cset.insert(GpData::ConstItem(0.0, "0.0", 1.0));


	//auto gp_data = std::make_shared<GpData>(bset,uset,vset,cset, n_repeat, n_repeat);
	//auto gp_parser = GpParser(gp_data);

	//std::unique_ptr<IExpressionNode> thetha = std::make_unique<VariableNode>("thetha");
	//std::unique_ptr<IExpressionNode> phi = std::make_unique<VariableNode>("phi");
	//std::unique_ptr<IExpressionNode> thetha1 = std::make_unique<VariableNode>("thetha");
	//std::unique_ptr<IExpressionNode> phi1 = std::make_unique<VariableNode>("phi");

	//std::unique_ptr<IExpressionNode> minus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x - y; }, "-", std::move(thetha1), std::move(phi1));

	//std::unique_ptr<IExpressionNode> cos = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::cos(val); }, "cos", std::move(minus));
	//std::unique_ptr<IExpressionNode> sin = std::make_unique<UnaryNode>([](const arma::dmat& val) {return arma::sin(val); }, "sin", std::move(phi));


	//std::unique_ptr<IExpressionNode> plus = std::make_unique<BinaryNode>([](const arma::dmat& x, const arma::dmat& y) {return x + y; }, "+", std::move(cos), std::move(sin));


	//std::cout << "Constructed tree:\n" << plus->toString() << "\n";

	//std::unique_ptr<ExpressionTree> tree1 = std::make_unique<ExpressionTree>(std::move(plus));


	//json tree_json = gp_parser.parseTreeToJson(tree1);
	////std::cout << tree_json.dump(4) << "\n";
	//auto tree_from_json = gp_parser.parseJsonToTree(tree_json);

	//std::cout << "From json:\n" << tree_from_json->getRoot()->toString() << "\n";


	return 0;
}