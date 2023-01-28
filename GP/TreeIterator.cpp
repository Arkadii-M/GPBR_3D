#include "TreeIterator.h"

PostOrderTreeIterator::PostOrderTreeIterator(reference ptr):
	curr_ptr(ptr)
{
}

PostOrderTreeIterator::reference PostOrderTreeIterator::operator*() const
{
	return curr_ptr;
}

PostOrderTreeIterator& PostOrderTreeIterator::operator++()
{
	if (curr_ptr->getLeftSon())
	{
		curr_ptr.swap(curr_ptr->getLeftSon());
		//curr_ptr = curr_ptr->getLeftSon();
		//return PostOrderTreeIterator(curr_ptr->getLeftSon());
	}
	else if (curr_ptr->getRightSon())
	{

		//return PostOrderTreeIterator(curr_ptr->getRightSon());
	}
	return *this;
	// TODO: insert return statement here
}

PostOrderTreeIterator PostOrderTreeIterator::operator++(int)
{
	PostOrderTreeIterator tmp = *this;
	++(*this);
	return tmp;
}
