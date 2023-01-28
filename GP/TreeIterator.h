#pragma once
#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H
#include <iterator>
#include "ExpressionTree.h"

class PostOrderTreeIterator
{
public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::unique_ptr<IExpressionNode>;
    using pointer = std::unique_ptr<IExpressionNode>*;  // or also value_type*
    using reference = std::unique_ptr<IExpressionNode>&;  // or also value_type&

    PostOrderTreeIterator(reference ptr);

    reference operator*() const;
    //reference operator->();
     // Prefix increment
    PostOrderTreeIterator& operator++();
    PostOrderTreeIterator operator++(int);
    friend bool operator== (const PostOrderTreeIterator& a, const PostOrderTreeIterator& b);
    friend bool operator!= (const PostOrderTreeIterator& a, const PostOrderTreeIterator& b);

private:
    reference curr_ptr;
};

#endif // !TREE_ITERATOR_H
