#ifndef TREE_EXPRESSION_TREE_H
#define TREE_EXPRESSION_TREE_H
typedef unsigned int uint;

#include <memory>
#include <algorithm>
#include <iterator>

#include "../GPBR_3D/IExpressionNode.h"

class ExpressionTree {

private:
	uint total_nodes;
	std::unique_ptr<IExpressionNode> root;


	/// <summary>
	/// Tree traversal with handler.
	/// 	TODO: add some info
	/// </summary>
private:
	struct OrderHandler {
	public:
		OrderHandler() = default;
		virtual void onVisitLeft(){};
		virtual void onVisitRight(){};
		virtual void onEmpty(){};
		virtual void onReturn() {};
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) = 0;
	};
	struct EnumerateHandler : public OrderHandler{
	private:
		uint num {1};
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


	struct SwapByIndexHandler : public OrderHandler {
	private:
		const uint find_index;
		std::unique_ptr<IExpressionNode>& find_node;
	public:
		SwapByIndexHandler(uint index, std::unique_ptr<IExpressionNode>& to_set);

		// Inherited via OrderHandler
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
	};

	struct SwapTempHandler : public OrderHandler {
	private:
		std::unique_ptr<IExpressionNode>& find_node;
	public:
		SwapTempHandler(std::unique_ptr<IExpressionNode>& to_set);

		// Inherited via OrderHandler
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
	};

	struct ExtractSubTree : public OrderHandler {
	private:
		std::unique_ptr<IExpressionNode> sub_tree;
		const uint index;
	public:
		ExtractSubTree(uint index);
		std::unique_ptr<IExpressionNode> getResult();
		// Inherited via OrderHandler
		virtual bool operator()(std::unique_ptr<IExpressionNode>& node) override;
	};

	struct ReplaceNode : public OrderHandler {
	private:
		std::unique_ptr<IExpressionNode>& to_replace;
		const uint index;
	public:
		ReplaceNode(uint index, std::unique_ptr<IExpressionNode>& to_replace);
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


	std::unique_ptr<IExpressionNode>& getRoot();
	void enumerateNodes();

	uint getTotalNodes() const;
	uint getHeight() const;

	void recalculate();

	std::string print();

	static std::unique_ptr<IExpressionNode> SubTree(std::unique_ptr<ExpressionTree>& tree, const uint sub_index);
	static void ReplaceNode(std::unique_ptr<ExpressionTree>& tree, const uint index, std::unique_ptr<ExpressionTree>& to_replace);
	static bool Equal(const ExpressionTree& first, const ExpressionTree& second);
	static void SwapNodesAtPositions(
		std::unique_ptr<ExpressionTree>& first_tree,
		std::unique_ptr<ExpressionTree>& second_tree,
		const uint first_node_pos,
		const uint second_node_pos);

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
};

#endif // ! EXPRESSION_TREE_H
