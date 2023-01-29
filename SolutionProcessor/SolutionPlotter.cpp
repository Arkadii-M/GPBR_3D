#include "SolutionPlotter.h"

SolutionPlotter::SolutionPlotter(std::string exact_surface, uint n_thetha, uint n_phi):
	exact_surface(exact_surface),
	n_thetha(n_thetha),
	n_phi(n_phi),
	plot_exact(true)
{
	pipe.release();
}


void SolutionPlotter::plotToFile(const std::string G1, const std::string file_name)
{
	this->openPipe();
	// N thetha,N phi, G1 expression, G2 expression (if empty don't plot), file_name
	std::string call_str;
	if (plot_exact)
	{
		call_str = std::format("plot3dmesh({},{},'{}','{}','{}')\n",
			n_thetha,
			n_phi,
			G1,
			exact_surface,
			file_name);
	}
	else
	{
		call_str = std::format("plot3dmesh({},{},'{}','','{}')\n",
			n_thetha,
			n_phi,
			G1,
			file_name);
	}
	if (pipe)
	{
		fprintf(pipe.get(), call_str.c_str());
		fflush(pipe.get());  // flush the pipe
	}
	this->closePipe();
}

void SolutionPlotter::openPipe()
{
	pipe = std::make_unique<FILE>(_popen(OCTAVE_GUI_NAME, "w"));
}

void SolutionPlotter::closePipe()
{
	_pclose(pipe.get());
}
