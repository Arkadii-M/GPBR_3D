#pragma once
#ifndef POPULATION_H
#define POPULATION_H
#include <vector>
#include "Individuum.h"
#include <algorithm>
#include <numeric>

class Population
{
	using uint = unsigned int;
private:
	std::vector<std::shared_ptr<Individuum>> population;
public:
	Population();


	uint popSize() const;


	void insertOne(std::shared_ptr<Individuum> chr);
	void insertMany(std::vector<std::shared_ptr<Individuum>>& chr_arr);

	void deleteOne(std::weak_ptr<Individuum>& chr);
	void deleteMany(std::vector<std::weak_ptr<Individuum>>& chr_arr);
	void deleteOneAtPos(uint pos);

	std::weak_ptr<Individuum> getAt(uint pos);

	std::weak_ptr<Individuum> getBest(); // Get element with min fitness
	std::vector<std::weak_ptr<Individuum>> getNBest(uint n_best); // Get n elements with min fitness
	std::vector<std::weak_ptr<Individuum>> getNBestByDelta(const double delta); // Get elements wich fitness is in delta range
	void keepNBest(uint n_best);

	double bestFitness();
	double avgFitness();

	void clear();




	std::vector<std::shared_ptr<Individuum>>::iterator begin();
	std::vector<std::shared_ptr<Individuum>>::iterator end();
};

#endif //POPULATION_H