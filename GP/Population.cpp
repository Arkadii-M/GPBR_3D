#include "Population.h"

Population::Population()
{
	population = std::vector<std::shared_ptr<Individuum>>();
}

uint Population::popSize() const
{
	return population.size();
}

void Population::insertOne(std::shared_ptr<Individuum> chr)
{
	population.push_back(std::move(chr));
}

void Population::insertMany(std::vector<std::shared_ptr<Individuum>>& chr_arr)
{
	auto arrIt = chr_arr.begin();
	while (arrIt != chr_arr.end())
	{
		insertOne(*arrIt);
		arrIt++;
	}
}

void Population::deleteOne(std::weak_ptr<Individuum>& chr)
{
	auto popIt = population.begin();

	while (popIt != population.end())
	{
		if ((*popIt) == chr.lock())
		{
			population.erase(popIt);
			return;
		}
		popIt++;
	}
	int ps = population.size();
}

void Population::deleteMany(std::vector<std::weak_ptr<Individuum>>& chr_arr)
{
	auto arrIt = chr_arr.begin();
	while (arrIt != chr_arr.end())
	{
		deleteOne(*arrIt);
		arrIt++;
	}
}

void Population::deleteOneAtPos(uint pos)
{
	population.erase(population.begin() + pos);
}

std::weak_ptr<Individuum> Population::getAt(uint pos)
{
	return population.at(pos);
}

std::weak_ptr<Individuum> Population::getBest()
{
	return *std::min_element(population.begin(), population.end(), Individuum::cmp_weak);
}

double Population::bestFitness()
{
	return getBest().lock()->getFintness();
}

double Population::avgFitness()
{
	return (std::accumulate(population.begin(), population.end(), 0.0f, Individuum::sum_weak) / (double)this->popSize());
}

void Population::clear()
{
	this->population.clear();
}

std::vector<std::shared_ptr<Individuum>>::iterator Population::begin() {
	return population.begin();
}
std::vector<std::shared_ptr<Individuum>>::iterator Population::end(){
	return population.end();
}