#pragma once
#ifndef GP_ITEM_H
#define GP_ITEM_H
#include <string>

template<typename Type>
class GpItem {
private:
	Type item;
	const std::string name;
	const double select_proba;
	double cumulative_prob;
public:
	GpItem():
		item(nullptr),
		name(""),
		select_proba(-1.0),
		cumulative_prob(-1.0)
	{

	}
	GpItem(Type item, std::string name, double prob) :
		item(item),
		name(name),
		select_proba(prob),
		cumulative_prob(-1.0)
	{

	}
	double getProbability() const { return select_proba; }
	void setCumulativeProbability(double prob) { cumulative_prob = prob; }
	double getCumulativeProbability() const { return cumulative_prob; }
	std::string getName() const { return name; }
	Type getItem() const { return item; }
	bool operator<(const GpItem<Type>& rhs) const
	{
		//return name < rhs.name;  //assume that you compare the record based on a
		return cumulative_prob < rhs.cumulative_prob;
	}
	GpItem<Type>& operator=(const GpItem<Type>& rhs)
	{
		//if (this == &rhs)
		//	return *this;

		//item = rhs.item;
		//name = rhs.name;
		//select_proba = rhs.select_proba;
		//cumulative_prob = rhs.cumulative_prob;
		//return *this;
		if (this != &rhs)
			std::construct_at(this, rhs);  // no destruction needed since trivially destructable

		return *this;
	}
};


#endif // !GP_ITEM_H
