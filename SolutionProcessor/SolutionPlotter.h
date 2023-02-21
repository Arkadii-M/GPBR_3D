#pragma once
#include <memory>
#include <string>
#include <format>

#ifndef SOLUTION_PLOTTER_H
#define SOLUTION_PLOTTER_H

#define OCTAVE_GUI_NAME "octave-gui --persist"


# define M_PI           3.14159265358979323846  /* pi */

class SolutionPlotter
{
public:

	typedef unsigned int uint;
	enum class SolutionPlotMode{ Both,	Single,	Diff };
private:
	//std::unique_ptr<FILE>  pipe;
	FILE* pipe;
	const uint n_thetha;
	const uint n_phi;
	std::string exact_surface;
	bool plot_exact;
	const SolutionPlotMode mode;
	std::string mode_str;
public:

	SolutionPlotter(std::string exact_surface, uint n_thetha,uint n_phi, SolutionPlotMode mode);
	~SolutionPlotter() = default;

	void plotToFile(const std::string G1_approx, const std::string file_name);

	//static uint s_n_thetha;
	//static uint s_n_phi;
	//static std::string s_exact_surface;
	//static std::string s_mode_str;
	//static void plotToFileStatic(const std::string G1_approx, const std::string file_name);


private:
	void openPipe();
	void closePipe();

};

#endif // !BR_PLOT_H
