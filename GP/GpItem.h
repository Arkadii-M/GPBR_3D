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
public:
	GpItem(Type item, std::string name, double prob) :
		item(item),
		name(name),
		select_proba(prob)
	{

	}
	double getProbability() const { return select_proba; }
	std::string getName() const { return name; }
	Type getItem() const { return item; }
	bool operator<(const GpItem<Type>& rhs) const
	{
		return name < rhs.name;  //assume that you compare the record based on a
	}
};


#endif // !GP_ITEM_H
