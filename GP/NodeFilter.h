#pragma once
#include <vector>
#include <memory>
#include "NodeObserver.h"
#ifndef NODE_FILTER_H
#define NODE_FILTER_H

class NodeFilter
{
public:
	using uint = unsigned int;
	using node_arg = const std::unique_ptr<NodeObserver>&;
	using node_filter = std::function<bool(node_arg node)>;
	const node_filter filter;
private:
	std::vector<uint> filtered_indexes;
public:
	NodeFilter(node_filter filter);
	void operator()(std::unique_ptr<NodeObserver>& node);
	std::vector<uint> getFilteredIndexes() const;
};

#endif // !NODE_FILTER_H
