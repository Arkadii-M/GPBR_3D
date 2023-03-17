#ifndef TREE_EXPRESSION_TREE_H
#define TREE_EXPRESSION_TREE_H
typedef unsigned int uint;

#include <memory>
#include <algorithm>
#include <iterator>
#include <variant>

#include "IExpressionNode.h"
#include "TempNode.h"
#include "NodeObserver.h"
#include "NodeFilter.h"
#include "TreeTraversal.h"


class ExpressionTree {

private:
	uint total_nodes;
	std::unique_ptr<IExpressionNode> root;

public:
	static void SwapSubTress(
		std::unique_ptr<ExpressionTree>& first_tree,
		std::unique_ptr<ExpressionTree>& second_tree,
		std::unique_ptr<NodeObserver>& first_observe,
		std::unique_ptr<NodeObserver>& second_observe);
	static void ReplaceNodes(
		std::unique_ptr<ExpressionTree>& first_tree,
		std::unique_ptr<ExpressionTree>& second_tree,
		std::unique_ptr<NodeObserver>& first_observe,
		std::unique_ptr<NodeObserver>& second_observe);

	std::unique_ptr<NodeObserver> getRootObserver();
	std::unique_ptr<NodeObserver> getNodeObserver(uint node_id);

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
		std::unique_ptr<NodeObserver> observer;
	public:
		ObserverExtract(uint id);
		std::unique_ptr<NodeObserver> getObserver();
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

	std::vector<uint> filterNodes(NodeFilter filter);

	std::unique_ptr<IExpressionNode> SubTree(std::unique_ptr<ExpressionTree>& tree, const uint sub_index);

	arma::dmat evaluate(const arma::dmat& thetha, const arma::dmat& phi);

	//TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi, const TreeDerivativeInfo& dinfo);
	TreeDerivative autoDiffReverse(const arma::dmat& thetha, const arma::dmat& phi,
		TreeDerivative::PartialDerivativeStrategy strategy = TreeDerivative::PartialDerivativeStrategy::OnlyConstsDerivative);
};

#endif // ! EXPRESSION_TREE_H
