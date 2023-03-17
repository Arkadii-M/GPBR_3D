#include "TreeTraversal.h"


void TreeTraversal::preOrder(std::unique_ptr<NodeObserver> observer, NodeFilter& filter)
{
	if (!observer)
		return;

	filter(observer);
	preOrder(observer->getLeft(),filter);
	preOrder(observer->getRight(), filter);
}
