#pragma once
#ifndef R_MODEL_SELCTOR_H
#define R_MODEL_SELCTOR_H
#include <memory>
#include "../GP/random.hpp"
#include "../GP/Individuum.h"
#include "../GP/Population.h"

using Random = effolkronium::random_static;
class RModelSelector
{
	typedef unsigned int uint;
private:
	const double p_mutate;
	const double p_crossove;
	const uint r_param;
	const uint tournament_param;

	std::vector<std::shared_ptr<Individuum>> parents;
	std::vector<std::weak_ptr<Individuum>> to_mutate;
	std::vector<std::pair<std::weak_ptr<Individuum>, std::weak_ptr<Individuum>>> to_crossove;


	std::vector<std::weak_ptr<Individuum>> to_delete;


public:
	RModelSelector(double p_mut, double p_cross, uint r_param, uint tournament_chose);
	~RModelSelector() = default;
	void makeSelection(Population& population);


	std::vector<std::shared_ptr<Individuum>>& getParents();
	std::vector<std::weak_ptr<Individuum>>& getToMutate();
	std::vector<std::pair<std::weak_ptr<Individuum>, std::weak_ptr<Individuum>>>& getToCrossove();

	std::vector<std::weak_ptr<Individuum>>& getToDelete();

private:
	void selectParents(Population& population);
	void selectToDelete(Population& population);

	void selectForMutationAndCrossover();

	bool inParents(std::weak_ptr<Individuum> ind);
	bool inDelete(std::weak_ptr<Individuum> ind);

	void clearVectors();
};

#endif // !R_MODEL_SELCTOR_H
