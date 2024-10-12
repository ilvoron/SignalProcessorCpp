/**
 * @file TGnuPlotViewer.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TFileWriter class, TGnuPlotViewer
 * class, responsible for managing GnuPlot visualizations of signal data.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TGnuPlotViewer.hpp"
#include "TCore.hpp"

#include <cstdlib>
#include <fstream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

/*
 * PUBLIC METHODS
 */

TGnuPlotViewer::TGnuPlotViewer(
    std::vector<std::string>                filePaths,
    std::optional<std::vector<std::string>> graphLabels,
    std::optional<std::string>              xLabel,
    std::optional<std::string>              yLabel,
    std::string                             gnuPlotPath)
    : _params{.filePaths   = std::move(filePaths),
              .graphLabels = std::move(graphLabels),
              .xLabel      = std::move(xLabel),
              .yLabel      = std::move(yLabel),
              .gnuPlotPath = std::move(gnuPlotPath)} {
    if (_params.filePaths.size() != _params.graphLabels->size()) {
        throw SignalProcessingError(
            "Number of files does not match number of labels");
    }
}

TGnuPlotViewer::TGnuPlotViewer(TGnuPlotViewerParams params)
    : _params(std::move(params)) {
    if (_params.filePaths.size() != _params.graphLabels->size()) {
        throw SignalProcessingError(
            "Number of files does not match number of labels");
    }
}

const TGnuPlotViewerParams& TGnuPlotViewer::getParams() const {
    return _params;
}

bool TGnuPlotViewer::isExecuted() const {
    return _isExecuted;
}

void TGnuPlotViewer::execute() const {
    _isExecuted = false;

    // Check if the files exist
    for (const auto& filePath : _params.filePaths) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw SignalProcessingError("Can't find file: \"" + filePath +
                                        "\"");
        }
        file.close();
    }

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || \
    defined(__MINGW64__)

    std::string command =
        "start /B cmd /c \"\"" + _params.gnuPlotPath + "\" -persist -e \"";

    if (_params.xLabel) {
        command += "set xlabel '" + *_params.xLabel + "'; ";
    }
    if (_params.yLabel) {
        command += "set ylabel '" + *_params.yLabel + "'; ";
    }

    command += "plot ";
    for (size_t i = 0; i < _params.filePaths.size(); ++i) {
        command += "'" + _params.filePaths[i] + "' using 1:2 with lines";
        if (_params.graphLabels) {
            command += " title '" + (*_params.graphLabels)[i] + "'";
        }
        if (i < _params.filePaths.size() - 1) {
            command += ", ";
        }
    }

    command += "\"\"";
    system(command.c_str());

#else

    std::string command = _params.gnuPlotPath + " -persist -e \"";

    if (_params.xLabel) {
        command += "set xlabel '" + *_params.xLabel + "'; ";
    }
    if (_params.yLabel) {
        command += "set ylabel '" + *_params.yLabel + "'; ";
    }

    command += "plot ";
    for (size_t i = 0; i < _params.filePaths.size(); ++i) {
        command += "'" + _params.filePaths[i] + "' using 1:2 with lines";
        if (_params.graphLabels) {
            command += " title '" + (*_params.graphLabels)[i] + "'";
        }
        if (i < _params.filePaths.size() - 1) {
            command += ", ";
        }
    }

    command += "\"";
    system(command.c_str());

#endif

    _isExecuted = true;
}
