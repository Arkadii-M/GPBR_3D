#include "RModelSelector.h"

RModelSelector::RModelSelector(double p_mut, double p_cross, uint r_param, uint tournament_chose):
	p_mutate(p_mut),
	p_crossove(p_cross),
	r_param(r_param),
	tournament_param(tournament_chose)
{
	parents = std::vector<std::shared_ptr<Individuum>>();
	to_mutate = std::vector<std::weak_ptr<Individuum>>();
	to_delete = std::vector<std::weak_ptr<Individuum>>();
	to_crossove = std::vector<std::pair<std::weak_ptr<Individuum>, std::weak_ptr<Individuum>>>();
}

void RModelSelector::makeSelection(Population& population)
{
	this->clearVectors();
	this->selectParents(population);
	this->selectToDelete(population);

	this->selectForMutationAndCrossover();
}

std::vector<std::shared_ptr<Individuum>>& RModelSelector::getParents()
{
	return parents;
}

std::vector<std::weak_ptr<Individuum>>& RModelSelector::getToMutate()
{
	return to_mutate;
}

std::vector<std::pair<std::weak_ptr<Individuum>, std::weak_ptr<Individuum>>>& RModelSelector::getToCrossove()
{
	return to_crossove;
}

std::vector<std::weak_ptr<Individuum>>& RModelSelector::getToDelete()
{
	return to_delete;
}

void RModelSelector::selectParents(Population& population)
{
	uint chosen = 0;
	uint selected = 0;
	auto to_select = std::vector<std::weak_ptr<Individuum>>();
	while (chosen < this->r_param)
	{
		selected = 0;
		while (selected < this->tournament_param)
		{
			auto ind =*Random::get(population.begin(), population.end());
		/*	auto id = Random::get(0, population.popSize() - 1);
			auto ind = population.getAt(id);*/
			if (!inParents(ind))
			{
				to_select.push_back(ind);
				selected++;
			}
		}
		auto min_ind = *std::min_element(to_select.begin(), to_select.end(), Individuum::cmp_weak);
		auto to_insert = std::make_shared<Individuum>(*min_ind.lock());
		to_insert->setCalculated(false);
		parents.push_back(to_insert); // copy
		to_select.clear();
		chosen++;
	}
}

void RModelSelector::selectToDelete(Population& population)
{
	uint chosen = 0;
	uint selected = 0;
	auto to_del = std::vector<std::weak_ptr<Individuum>>();
	while (chosen < this->r_param)
	{
		selected = 0;
		while (selected < this->tournament_param)
		{
			//auto id = Random::get(0, population.popSize() - 1);
			//auto ind = population.getAt(id);
			auto ind = *Random::get(population.begin(), population.end());
			if (!inDelete(ind))
			{
				to_del.push_back(ind);
				selected++;
			}
		}
		auto min_ind = *std::max_element(to_del.begin(), to_del.end(), Individuum::cmp_weak);
		to_delete.push_back(min_ind);
		to_del.clear();
		chosen++;
	}
}

void RModelSelector::selectForMutationAndCrossover()
{
	Random::shuffle(parents.begin(), parents.end()); // Shuffle the parents
	auto crossove_probabilities = Random::get<std::vector>(0.0, 1.0, parents.size());
	auto mutate_probabilities = Random::get<std::vector>(0.0, 1.0, parents.size());

	bool pair_filled = true;
	std::pair <std::weak_ptr<Individuum>, std::weak_ptr<Individuum>> pair;

	auto parentsIt = parents.begin();
	auto crossIt = crossove_probabilities.begin();
	auto mutIt = mutate_probabilities.begin();

	while (parentsIt < parents.end())
	{
		if (*crossIt < this->p_crossove)
		{
			if (pair_filled)
			{
				pair.first = *parentsIt;
				pair_filled = false;
			}
			else
			{
				pair.second = *parentsIt;
				this->to_crossove.push_back(pair);
				pair_filled = true;
			}
		}
		if (*mutIt < this->p_mutate)
		{
			this->to_mutate.push_back(*parentsIt);
		}
		parentsIt++;
		crossIt++;
		mutIt++;
	}
}

bool RModelSelector::inParents(std::weak_ptr<Individuum> ind)
{
	return (std::find(parents.begin(), parents.end(), ind) != parents.end());// check if contains

	//auto pIt = parents.begin();

	//while (pIt != parents.end())
	//{
	//	if (*pIt == ind.lock())
	//		return true;
	//	pIt++;
	//}
	//return false;
}

bool RModelSelector::inDelete(std::weak_ptr<Individuum> ind)
{
	return (std::find(to_delete.begin(), to_delete.end(), ind) != to_delete.end());// check if contains
	//auto delIt = to_delete.begin();

	//while (delIt != to_delete.end())
	//{
	//	if (*delIt == ind.lock())
	//		return true;
	//	delIt++;
	//}
	//return false;
}

void RModelSelector::clearVectors()
{
	parents.clear();
	to_mutate.clear();
	to_crossove.clear();
	to_delete.clear();
}
