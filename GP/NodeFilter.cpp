#include "NodeFilter.h"

NodeFilter::NodeFilter(node_filter filter):
	filter(filter)
{
	//filtered_nodes = std::vector<std::unique_ptr<NodeObserver>>();
}

void NodeFilter::operator()(std::unique_ptr<NodeObserver>& node)
{
	if (node->isNull())
		return;

	if (filter(node))
		filtered_indexes.push_back(node->getNum());
}

std::vector<uint> NodeFilter::getFilteredIndexes() const
{
	return filtered_indexes;
}
