#include "SolutionPlotter.h"

SolutionPlotter::SolutionPlotter(std::string exact_surface, uint n_thetha, uint n_phi, SolutionPlotMode mode):
	exact_surface(exact_surface),
	n_thetha(n_thetha),
	n_phi(n_phi),
	plot_exact(true),
	mode(mode)
{
	switch (mode)
	{
	case SolutionPlotMode::Both:
		mode_str = "both";
		//SolutionPlotter::s_mode_str = "both";
		break;
	case SolutionPlotMode::Single:
		mode_str = "single";
		//SolutionPlotter::s_mode_str = "single";
		break;
	case SolutionPlotMode::Diff:
		mode_str = "diff";
		//SolutionPlotter::s_mode_str = "diff";
		break;
	default:
		throw std::invalid_argument("Invalid plot mode");
		break;
	}
	//SolutionPlotter::s_n_thetha = n_thetha;
	//SolutionPlotter::s_n_phi = n_phi;
	//SolutionPlotter::s_exact_surface = exact_surface;
	//pipe.release();
}


void SolutionPlotter::plotToFile(const std::string G1_approx, const std::string file_name)
{
	this->openPipe();
	// N thetha,N phi, G1 expression, G2 expression (if empty don't plot), file_name
	std::string call_str = std::format(
		"plot3dmesh({},{},'{}','{}','{}','{}')\n",
		n_thetha,n_phi,
		G1_approx,exact_surface,
		mode_str,
		file_name);

	if (pipe)
	{
		//fprintf(pipe.get(), call_str.c_str());
		//fflush(pipe.get());  // flush the pipe
		fprintf(pipe, call_str.c_str());
		fflush(pipe);  // flush the pipe
	}
	this->closePipe();
}
//void SolutionPlotter::plotToFileStatic(const std::string G1_approx, const std::string file_name)
//{
//	auto pipe = _popen(OCTAVE_GUI_NAME, "w");
//	std::string call_str = std::format(
//		"plot3dmesh({},{},'{}','{}','{}','{}')\n",
//		s_n_thetha, s_n_phi,
//		G1_approx, s_exact_surface,
//		s_mode_str,
//		file_name);
//	if (pipe)
//	{
//		fprintf(pipe, call_str.c_str());
//		fflush(pipe);  // flush the pipe
//	}
//	_pclose(pipe);
//}

void SolutionPlotter::openPipe()
{
	//pipe = std::make_unique<FILE>(_popen(OCTAVE_GUI_NAME, "w"));
	pipe = _popen(OCTAVE_GUI_NAME, "w");
}

void SolutionPlotter::closePipe()
{
	_pclose(pipe);
}
