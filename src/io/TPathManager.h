/**
 * TODO: Add automatic detection of GnuPlot path.
 * TODO: Add compatibility for Windows and Unix systems.
 */

#pragma once

#include <string>

/**
 * @namespace PM
 * @brief Contains default paths and configurations for file management.
 */
namespace PM {

static const std::string DEFAULT_SIGNAL_LINE_FILEPATH =
    "signal.txt";  ///< Default file path for saving signal lines.
static const std::string DEFAULT_GNUPLOT_PATH =
    "gnuplot";  ///< Default path to the gnuplot executable.

}  // namespace PM