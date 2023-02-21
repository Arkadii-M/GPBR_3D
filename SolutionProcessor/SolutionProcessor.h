#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <chrono>
#include <map>
#include <future>
#include "SolutionPlotter.h"
#include "../GP/Population.h"
#include "../GP/GpParser.h"
#ifndef SOLUTION_PROCESSING_H
#define SOLUTION_PROCESSING_H

namespace fs = std::filesystem;

#define CSV_HISTORY_FULL_FILE_NAME "full_history.csv"
#define POPULATION_FILE_NAME "population.json"
#define INFO_FILE "info.txt"
#define PLOTS_FOLDER_NAME "plots"
#define RESULTS_FOLDER_NAME "results"

class SolutionProcesser
{
public:
	using uint = unsigned int;
	struct IterationHistory
	{
		const uint iter; // iteration number
		const uint pop_size; // population size
		const double fitness; // fitness of the best solution
		const double avg_fitness; // average fitness
		const std::string solution; // found tree representation
		const std::chrono::milliseconds time_ms; // iteration time
	};
private:
	std::vector<IterationHistory> history;
	std::unique_ptr<SolutionPlotter> plotter;
	std::shared_ptr<GpParser> parser;

	fs::path path;
	fs::path main_folder;

	bool plot_on_new_solution;
	bool print_progress;
public:
	SolutionProcesser(std::string path_to, std::unique_ptr<SolutionPlotter> plotter, std::shared_ptr<GpParser> parser);

	void createInfoFile(std::string info);
	void appendOne(IterationHistory hist);
	void savePopulation(Population& pop);

	void plotOnNewSolution(bool plot);
	void printProgress(bool prog);

private:
	void printProgress(const IterationHistory& hist);
	void appendToCsv();
	void createStructure();




};
#endif // !SOLUTION_PROCESSING_H
