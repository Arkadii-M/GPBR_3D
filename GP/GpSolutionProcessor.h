#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <chrono>
#ifndef SOLUTION_PROCESSING_H
#define SOLUTION_PROCESSING_H

namespace fs = std::filesystem;

#define CSV_HISTORY_FILE_NAME "fitness_history.csv"
#define CSV_HISTORY_FULL_FILE_NAME "full_history.csv"
#define CSV_HISTORY_WITH_SOLUTIONS_FILE_NAME "fitness_history_with_solutions.csv"
#define INFO_FILE "info.txt"
#define PLOTS_FOLDER_NAME "plots"
#define RESULTS_FOLDER_NAME "results"

class SolutionProcesser
{
	std::unique_ptr<BrPlotter> ProblemPlotter;
	std::map<int, double> fitness_history;
	std::map<int, std::string> best_history;
	std::map<int, std::tuple<double, std::string, std::chrono::milliseconds>> full_history; // iter - {fitness,function,iteration time (ms)}
	fs::path path;
	fs::path main_folder;
	bool plot_on_new_solution;
public:
	SolutionProcesser(std::string path_to, std::unique_ptr<BrPlotter> plotter);

	void CreateInfoFile(std::string info);
	void AppendOne(std::weak_ptr<Individuum> ind, std::chrono::milliseconds iter_time);

	void EnablePlotOnNewSolution();
	void DisablePlotOnNewSolution();

	void Reset();


private:
	void AppendFitnessCsv();
	void AppendBestCsv();
	void AppendFullCsv();

	void CreateStructure();




};
#endif // !SOLUTION_PROCESSING_H
