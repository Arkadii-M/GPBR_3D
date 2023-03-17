#pragma once
#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H
#include <memory>
#include "NodeObserver.h"
#include "NodeFilter.h"
class TreeTraversal
{
public:
	static void preOrder(std::unique_ptr<NodeObserver> observer,NodeFilter & filter);

};

#endif // !TREE_TRAVERSAL_H
