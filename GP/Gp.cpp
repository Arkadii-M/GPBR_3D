#include "Gp.h"

GP::GP(std::unique_ptr<Evaluator> ev, std::shared_ptr<TreeGenerator> gen, uint max_n_change,
	double delta):
	eval(std::move(ev)),
	generator(std::move(gen)),
	max_no_change_iter(max_n_change),
	delta_max(delta)
{
}

void GP::setMaxNoChangeIter(uint no_change)
{
	max_no_change_iter = no_change;
}

void GP::setFindError(double err)
{
	delta_max = err;
}

std::weak_ptr<Individuum> GP::GetBest()
{
	return population.getBest();
}

Population& GP::GetPopulation()
{
	return population;
}
