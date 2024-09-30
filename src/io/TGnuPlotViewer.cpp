#include "TGnuPlotViewer.h"
#include "TCore.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

/*
 * PUBLIC METHODS
 */

TGnuPlotViewer::TGnuPlotViewer(std::vector<std::string> filePaths,
                               std::string xLabel,
                               std::string yLabel,
                               std::vector<std::string> graphLabels,
                               std::string gnuPlotPath)
    : _params{std::move(filePaths), std::move(xLabel), std::move(yLabel),
              std::move(graphLabels), std::move(gnuPlotPath)} {}

TGnuPlotViewer::TGnuPlotViewer(TGnuPlotViewerParams params)
    : _params(std::move(params)) {}

const TGnuPlotViewerParams& TGnuPlotViewer::getParams() const {
  return _params;
}

void TGnuPlotViewer::execute() const {
  if (_params.filePaths.size() != _params.graphLabels.size()) {
    throw SignalProcesserException(
        "Number of files does not match number of labels");
  }

  for (const auto& filePath : _params.filePaths) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
      throw SignalProcesserException("Can't find file: \"" + filePath + "\"");
    }
    file.close();
  }

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || \
    defined(__MINGW64__)
  std::string command = "start /B cmd /c \"\"" + _params.gnuPlotPath +
                        "\" -persist -e \"set xlabel '" + _params.xLabel +
                        "'; set ylabel '" + _params.yLabel + "'; ";

  command += "plot ";
  for (size_t i = 0; i < _params.filePaths.size(); ++i) {
    command += "'" + _params.filePaths[i] + "' using 1:2 with lines title '" +
               _params.graphLabels[i] + "'";
    if (i < _params.filePaths.size() - 1) {
      command += ", ";
    }
  }

  command += "\"\"";
  system(command.c_str());

#else
  std::string command = _params.gnuPlotPath + " -persist -e \"set xlabel '" +
                        _params.xLabel + "'; set ylabel '" + _params.yLabel +
                        "'; ";

  command += "plot ";
  for (size_t i = 0; i < _params.filePaths.size(); ++i) {
    command += "'" + _params.filePaths[i] + "' using 1:2 with lines title '" +
               _params.graphLabels[i] + "'";
    if (i < _params.filePaths.size() - 1) {
      command += ", ";
    }
  }

  command += "\"";
  system(command.c_str());
#endif
}
