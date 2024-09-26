#include "TCore.h"
#include "TGnuPlotViewer.h"
#include "TSignalLine.h"
#include <fstream>

// PUBLIC

TGnuPlotViewer::TGnuPlotViewer(const std::string& filePath,
                               const std::string& gnuPlotPath,
                               const std::string& xLabel,
                               const std::string& yLabel,
                               const std::string& graphLabel)
	: _params{filePath, gnuPlotPath, xLabel, yLabel, graphLabel} {}

TGnuPlotViewer::TGnuPlotViewer(TGnuPlotViewerParams params)
	: _params(params) {}

const TGnuPlotViewerParams& TGnuPlotViewer::getParams() const { return _params; }

void TGnuPlotViewer::execute() {
	std::ifstream file(_params.filePath);
	if (!file.is_open()) { THROW_SIGNAL_PROCESSOR_EXCEPTION("Can't find file: \"" + _params.filePath + "\""); }
	else { file.close(); }
	#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__)
		std::string command = "cmd /c \"\"" + _params.gnuPlotPath + "\" -persist -e \"set xlabel '" + _params.xLabel + "'; set ylabel '" + _params.yLabel + "'; plot '" + _params.filePath + "' using 1:2 with lines title '" + _params.graphLabel + "'\"\"";
		system(command.c_str());
	#else
		std::string command = _params.gnuPlotPath + " -persist -e \"set xlabel '" + _params.xLabel + "'; set ylabel '" + _params.yLabel + "'; plot '" + _params.filePath + "' using 1:2 with lines title '" + _params.graphLabel + "'\"";
		system(command.c_str());
	#endif
}