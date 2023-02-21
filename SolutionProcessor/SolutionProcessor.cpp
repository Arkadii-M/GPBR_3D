#include "SolutionProcessor.h"

SolutionProcesser::SolutionProcesser(std::string path_to, std::unique_ptr<SolutionPlotter> plotter, std::shared_ptr<GpParser> parser) :
	plotter(std::move(plotter)),
	parser(parser),
	main_folder(path_to),
	path(path_to),
	plot_on_new_solution(true),
	print_progress(true)
{
	history = std::vector<IterationHistory>();
	createStructure();
}

void SolutionProcesser::createInfoFile(std::string info)
{
	auto f_s_full_hist = std::ofstream{ path / INFO_FILE,std::ofstream::trunc };
	f_s_full_hist << std::format("Info about run:\n{}\n", info);
	f_s_full_hist.close();
}

void SolutionProcesser::appendOne(IterationHistory hist)
{
	history.push_back(hist);
	if (plot_on_new_solution)
	{
		if (history.size() == 1 || hist.fitness < (history.end()-2)->fitness)// first solution
		{
			plotter->plotToFile(hist.solution, std::format("{}/iteration_{}", (path / PLOTS_FOLDER_NAME).string(), hist.iter));
			//plotter->plotToFile(hist.solution, std::format("{}/{}/iteration_{}", path.string(), PLOTS_FOLDER_NAME, hist.iter));
			//std::async(std::launch::async, SolutionPlotter::plotToFileStatic, hist.solution, std::format("{}/{}/iteration_{}", path.string(), PLOTS_FOLDER_NAME, hist.iter));
		}
	}
	if (print_progress)
		printProgress(hist);

	this->appendToCsv();
}

void SolutionProcesser::savePopulation(Population& pop)
{
	auto population_file = std::ofstream{ path / POPULATION_FILE_NAME,std::ofstream::trunc };
	population_file << parser->parsePopulationToJson(pop).dump();
	population_file.close();
}

void SolutionProcesser::plotOnNewSolution(bool plot)
{
	plot_on_new_solution = plot;
}

void SolutionProcesser::printProgress(bool prog)
{
	print_progress = prog;
}

void SolutionProcesser::printProgress(const IterationHistory& hist)
{
	std::cout << "Population size: " << hist.pop_size << std::endl;
	std::cout << "Iteration: " << hist.iter << std::endl;
	std::cout << "min fitness: " << hist.fitness << std::endl;
	std::cout << "Avg fitness: " << hist.avg_fitness << std::endl;
	std::cout << "Best in iteration:" << std::endl;
	std::cout << std::format("R: {}", hist.solution);
	std::cout << "\n----------------------------------------------------------------------------" << std::endl;
}

void SolutionProcesser::appendToCsv()
{
	auto hIt = history.rbegin();
	auto fs_hist = std::ofstream{ path / CSV_HISTORY_FULL_FILE_NAME,std::ofstream::app };
	
	fs_hist << std::format("{},{},{},{},\"{}\",{}\n",
		hIt->iter,
		hIt->pop_size,
		hIt->fitness,
		hIt->avg_fitness,
		hIt->solution,
		hIt->time_ms
		);
	fs_hist.close();
}

void SolutionProcesser::createStructure()
{
	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm current;

	std::stringstream time_to_path;
	_localtime64_s(&current, &timenow);
	time_to_path << std::put_time(&current, "%Y_%m_%d__%H_%M_%S");

	std::cout << "Time is " << time_to_path.str() << std::endl;


	path = main_folder / std::format("results_{}", time_to_path.str());
	const fs::path plots{ path / "plots" };


	if (!fs::exists(path))
		fs::create_directories(path);


	if (!fs::exists(plots))
		fs::create_directory(plots);


	// create history file
	auto f_s_full_hist = std::ofstream{ path / CSV_HISTORY_FULL_FILE_NAME,std::ofstream::trunc };
	f_s_full_hist << "iteration,population size,fitness,average fitness,solution,iteration time(ms)\n";
	f_s_full_hist.close();


}
