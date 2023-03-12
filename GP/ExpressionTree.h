#ifndef TREE_EXPRESSION_TREE_H
#define TREE_EXPRESSION_TREE_H
typedef unsigned int uint;

#include <memory>
#include <algorithm>
#include <iterator>
#include <variant>

#include "IExpressionNode.h"
#include "TempNode.h"

class ExpressionTree {

private:
	uint total_nodes;
	std::unique_ptr<IExpressionNode> root;

public:
	class NodeObserve {
	private:
		std::unique_ptr<IExpressionNode>& current;
	public:
		NodeObserve() = default;
		NodeObserve(std::unique_ptr<IExpressionNode>& curr);
		~NodeObserve() = default;

		std::unique_ptr<NodeObserve> getLeft() const;
		std::unique_ptr<NodeObserve> getRight() const;
		bool isLeaf() const;
		bool isVariable() const;
		bool isConstant() const;
		bool isUnary() const;
		bool isBinary() const;
		bool isNull() const;
		std::any getValue();

		std::string getName() const;
		uint getNum() const;
		std::string print() const;

		std::unique_ptr<IExpressionNode> subTreeCopy();
		static void SwapSubTrees(std::unique_ptr<NodeObserve>& first, std::unique_ptr<NodeObserve>& second);
		static void SwapSubTrees(std::unique_ptr<NodeObserve>& first, std::unique_ptr<IExpressionNode> second);
		static void ReplaceNodes(std::unique_ptr<NodeObserve>& first, std::unique_ptr<NodeObserve>& second);
		static void ReplaceNodes(std::unique_ptr<NodeObserve>& first, std::unique_ptr<IExpressionNode> second);
	};
	static void SwapSubTress(
		std::unique_ptr<ExpressionTree>& first_tree,
		std::unique_ptr<ExpressionTree>& second_tree,
		std::unique_ptr<NodeObserve>& first_observe,
		std::unique_ptr<NodeObserve>& second_observe);
	static void ReplaceNodes(
		std::unique_ptr<ExpressionTree>& first_tree,
		std::unique_ptr<ExpressionTree>& second_tree,
		std::unique_ptr<NodeObserve>& first_observe,
		std::unique_ptr<NodeObserve>& second_observe);

	std::unique_ptr<NodeObserve> getRootObserver();
	std::unique_ptr <NodeObserve> getNodeObserver(uint node_id);

	/// <summary>
	/// Tree traversal with handler.
	/// 	TODO: add some info
	/// </summary>
private:
	struct OrderHandler {
	public:
		OrderHandler() = default;
		virtual void onVisitLeft() {};
		virtual void onVisitRight() {};
		virtual void onEmpty() {};
		virtual void onReturn() {};
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) = 0;
	};
	struct EnumerateHandler : public OrderHandler {
	private:
		uint num{ 1 };
		uint total_nodes{ 0 };
		uint curr_d{ 0 };
	public:
		EnumerateHandler() = default;
		// Inherited via OrderHandler
		virtual void onVisitLeft() override;
		virtual void onVisitRight() override;
		virtual void onEmpty() override;
		virtual void onReturn() override;
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
		uint getTotalNodes() const;
	};

	struct HeightHandler : public OrderHandler {
	public:
		HeightHandler() = default;
		// Inherited via OrderHandler
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
	};
	struct ObserverExtract : public OrderHandler {
	private:
		const uint node_id;
		std::unique_ptr<NodeObserve> observer;
	public:
		ObserverExtract(uint id);
		std::unique_ptr<NodeObserve> getObserver();
		// Inherited via OrderHandler
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;

	};

	bool inOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler);
	bool preOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler);
	bool postOrder(std::unique_ptr<IExpressionNode>& node, std::unique_ptr<OrderHandler>& handler);

public:
	ExpressionTree(std::unique_ptr<IExpressionNode> root);
	ExpressionTree(const ExpressionTree& tree);
	~ExpressionTree() = default;

	void enumerateNodes();

	uint getTotalNodes() const;
	uint getHeight() const;

	void recalculate();

	std::string print();

	struct NodeFilter : public OrderHandler
	{
	private:
		std::vector<uint> filtered_indexes;
	public:
		NodeFilter();
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
		virtual bool selectCondition(const std::unique_ptr<IExpressionNode>& node) = 0;
		std::vector<uint> getResult();
	};
	std::vector<uint> filterNodesIdexes(std::unique_ptr<NodeFilter> filter);

	std::unique_ptr<IExpressionNode> SubTree(std::unique_ptr<ExpressionTree>& tree, const uint sub_index);

	arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi);
	TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo);
};

#endif // ! EXPRESSION_TREE_H
