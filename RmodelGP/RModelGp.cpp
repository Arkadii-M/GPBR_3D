#include "RModelGp.h"

RmodelGp::RmodelGp(std::unique_ptr<Evaluator> ev,
    std::shared_ptr<TreeGenerator> gen,
    std::unique_ptr<RModelSelector> select,
    std::vector<std::unique_ptr<GeneticOpretator>>& mut_operators,
    std::vector<std::unique_ptr<GeneticOpretator>>& cross_operators,
	std::unique_ptr<SolutionProcesser> processor):
    GP(std::move(ev), gen),
    selector(std::move(select)),
	processor(std::move(processor))
{
	mutate_operators = std::vector<std::unique_ptr<GeneticOpretator>>(0);
	crossove_operators = std::vector<std::unique_ptr<GeneticOpretator>>(0);
	mutate_cumulative = std::vector<std::pair<double, int>>(0);
	crossove_cumulative = std::vector<std::pair<double, int>>(0);

	double mut_prob_sum = 0.0;
	double cross_prob_sum = 0.0;

	for (auto& mut_op : mut_operators)
	{
		mut_prob_sum += mut_op->getApplyProbability();
		this->mutate_operators.push_back(std::move(mut_op));
	}

	for (auto& cross_op : cross_operators)
	{
		cross_prob_sum += cross_op->getApplyProbability();
		this->crossove_operators.push_back(std::move(cross_op));
	}

	for (int i = 0; i < this->mutate_operators.size(); ++i)
		this->mutate_cumulative.emplace_back(this->mutate_operators[i]->getApplyProbability(), i);

	for (int i = 0; i < this->crossove_operators.size(); ++i)
		this->crossove_cumulative.emplace_back(this->crossove_operators[i]->getApplyProbability(), i);


	for (auto& mut_s : this->mutate_cumulative)
		mut_s.first /= mut_prob_sum;

	for (auto& cross_s : this->crossove_cumulative)
		cross_s.first /= cross_prob_sum;

	std::sort(mutate_cumulative.begin(), mutate_cumulative.end());// sort by first element in pair
	std::sort(crossove_cumulative.begin(), crossove_cumulative.end());// sort by first element in pair
	double mut_cumulative = 0.0;
	double cross_cumulative = 0.0;

	for (auto& mut_s : this->mutate_cumulative)
	{
		mut_cumulative += mut_s.first;
		mut_s.first = mut_cumulative;
	}

	for (auto& cross_s : this->crossove_cumulative)
	{
		cross_cumulative += cross_s.first;
		cross_s.first = cross_cumulative;
	}

}

bool RmodelGp::execute(uint iter)
{
	uint no_change_iter = 0;
	double last_error = -1.0;
	double curr_error = 0.0;

	std::chrono::steady_clock sc;
	for (uint i = 0; i < iter; ++i)
	{
		auto start = sc.now();
		this->executeOne();
		auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
		auto time_span = static_cast<std::chrono::duration<double>>(end - start);   // measure time span between start & end
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_span);

		auto best = population.getBest();
		processor->appendOne(SolutionProcesser::IterationHistory{
			.iter = i+1,
			.pop_size = population.popSize(),
			.fitness = best.lock()->getFintness(),
			.avg_fitness = population.avgFitness(),
			.solution = best.lock()->getTree()->print(),
			.time_ms = duration
			});


		curr_error = best.lock()->getFintness();
		if (curr_error < delta_max)
			return true;

		if (curr_error < last_error)
			no_change_iter = 0;
		else
			if (++no_change_iter >= max_no_change_iter)
				return false;

		last_error = curr_error;

	}
	return true;
}

void RmodelGp::generatePopulation(uint pop_size)
{
	population.clear();

	for (int i = 0; i < pop_size; ++i)
	{
		auto ind = std::make_shared<Individuum>(generator->generateTree());
		population.insertOne(ind);
	}
	this->evaluatePopulation();
}

void RmodelGp::executeOne()
{
	selector->makeSelection(population);

	auto& parents = selector->getParents();
	auto& to_crossove = selector->getToCrossove();
	auto& to_mutate = selector->getToMutate();
	auto& to_delete = selector->getToDelete();

	auto CrossPairIt = to_crossove.begin();
	while (CrossPairIt < to_crossove.end())
	{
		double r = Random::get<double>(0.0, 0.9999);

		for (auto& cross_sel : crossove_cumulative)
		{
			if (r < cross_sel.first)
			{
				this->crossove_operators.at(cross_sel.second)->operator()((*CrossPairIt).first, (*CrossPairIt).second);
				break;
			}
		}
		CrossPairIt++;
	}


	auto MutIt = to_mutate.begin();
	while (MutIt < to_mutate.end())
	{
		double r = Random::get<double>(0.0, 0.9999);

		for (auto& mut_sel : mutate_cumulative)
		{
			if (r < mut_sel.first)
			{
				//this->mutate_operators.at(mut_sel.second)->Apply((*MutIt));
				this->mutate_operators.at(mut_sel.second)->operator()((*MutIt));
				break;
			}
		}
		MutIt++;
	}

	population.deleteMany(to_delete);
	population.insertMany(parents);

	this->evaluatePopulation();
}


void RmodelGp::evaluatePopulation()
{
	eval->evaluatePopulation(population);
}
