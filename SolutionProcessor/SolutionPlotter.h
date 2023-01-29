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
	typedef unsigned int uint;
private:
	std::unique_ptr<FILE>  pipe;

	const uint n_thetha;
	const uint n_phi;
	std::string exact_surface;
	bool plot_exact;
public:

	SolutionPlotter(std::string exact_surface, uint n_thetha,uint n_phi);
	~SolutionPlotter() = default;

	void plotToFile(const std::string G1, const std::string file_name);


private:
	void openPipe();
	void closePipe();

};

#endif // !BR_PLOT_H
