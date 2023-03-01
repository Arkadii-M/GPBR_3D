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

std::vector<std::weak_ptr<Individuum>> Population::getNBest(uint n_best)
{
	// sort
	std::sort(population.begin(), population.end(), Individuum::cmp_weak);

	return std::vector<std::weak_ptr<Individuum>>(population.begin(),std::next(population.begin(),n_best));
}

std::vector<std::weak_ptr<Individuum>> Population::getNBestByDelta(const double delta)
{
	// sort
	std::sort(population.begin(), population.end(), Individuum::cmp_weak);

	const double best_error = getBest().lock()->getFintness();

	auto last_it = std::find_if_not(population.begin(), population.end(), [&](const std::weak_ptr<Individuum>& ind) 
		{
			return abs(best_error - ind.lock()->getFintness()) < delta;
		});

	return std::vector<std::weak_ptr<Individuum>>(population.begin(), last_it);
}

void Population::keepNBest(uint n_best)
{
	// sort
	std::sort(population.begin(), population.end(),Individuum::cmp_weak);
	// keep first n
	population.erase(std::next(population.begin(),n_best), std::prev(population.end()));
	int ps = population.size();

}
double Population::bestFitness()
{
	return getBest().lock()->getFintness();
}

double Population::avgFitness()
{
	return ((double)std::accumulate(population.begin(), population.end(), 0.0, Individuum::sum_weak) / (double)this->popSize());
	//return 0.0; //TODO: change
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