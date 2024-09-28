#include "TGnuPlotViewer.h"
#include "TCore.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>

/**
 ** PUBLIC METHODS
 */

TGnuPlotViewer::TGnuPlotViewer(std::string filePath,
                               std::string xLabel,
                               std::string yLabel,
                               std::string graphLabel,
                               std::string gnuPlotPath)
    : _params{std::move(filePath), std::move(xLabel), std::move(yLabel),
              std::move(graphLabel), std::move(gnuPlotPath)} {}

TGnuPlotViewer::TGnuPlotViewer(TGnuPlotViewerParams params)
    : _params(std::move(params)) {}

const TGnuPlotViewerParams& TGnuPlotViewer::getParams() const {
  return _params;
}

void TGnuPlotViewer::execute() const {
  std::ifstream file(_params.filePath);
  if (!file.is_open()) {
    throw SignalProcesserException("Can't find file: \"" + _params.filePath +
                                   "\"");
  }
  file.close();
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || \
    defined(__MINGW64__)
  const std::string command =
      "start /B cmd /c \"\"" + _params.gnuPlotPath +
      "\" -persist -e \"set xlabel '" + _params.xLabel + "'; set ylabel '" +
      _params.yLabel + "'; plot '" + _params.filePath +
      "' using 1:2 with lines title '" + _params.graphLabel + "'\"\"";
  system(command.c_str());
#else
  const std::string command =
      _params.gnuPlotPath + " -persist -e \"set xlabel '" + _params.xLabel +
      "'; set ylabel '" + _params.yLabel + "'; plot '" + _params.filePath +
      "' using 1:2 with lines title '" + _params.graphLabel + "'\"";
  system(command.c_str());
#endif
}