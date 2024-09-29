/**
 * ? Make a method to setup gnu plot once (with only one argument - a path to
 * gnuplot) and use it multiple times ?
 * TODO: add multiple graphs in one plot
 * TODO: ??? make constuctor more flexible and simple ??? get info from signal
 * line itself ???
 * !TODO: add custom args for gnuplot
 */

#pragma once

#include "TFileWriter.h"
#include "TPathManager.h"
#include "TSignalLine.h"

#include <string>

/**
 * @struct TGnuPlotViewerParams
 * @brief Parameters for configuring the GnuPlot viewer.
 */
struct TGnuPlotViewerParams {
  std::string filePath;  ///< Path to the file containing the signal data.
  std::string xLabel =
      SL::DEFAULT_X_LABEL;  ///< (optional) Label for the X axis.
  std::string yLabel =
      SL::DEFAULT_Y_LABEL;  ///< (optional) Label for the Y axis.
  std::string graphLabel =
      SL::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
  std::string gnuPlotPath =
      PM::DEFAULT_GNUPLOT_PATH;  ///< (optional) Path to the GnuPlot executable.
};

/**
 * @class TGnuPlotViewer
 * @brief Class responsible for visualizing a signal using GnuPlot.
 *
 * This class allows plotting a signal stored in a file using the GnuPlot tool.
 * It is configurable through a set of parameters including the file path,
 * GnuPlot path, and axis labels.
 */
class TGnuPlotViewer {
 public:
  /**
   * @brief Constructs a TGnuPlotViewer with specified parameters.
   *
   * @param filePath The path to the file containing the signal data.
   * @param gnuPlotPath (optional) The path to the GnuPlot executable.
   * @param xLabel (optional) The label for the X axis.
   * @param yLabel (optional) The label for the Y axis.
   * @param graphLabel (optional) The label for the graph.
   */
  TGnuPlotViewer(std::string filePath,
                 std::string xLabel = SL::DEFAULT_X_LABEL,
                 std::string yLabel = SL::DEFAULT_Y_LABEL,
                 std::string graphLabel = SL::DEFAULT_GRAPH_LABEL,
                 std::string gnuPlotPath = PM::DEFAULT_GNUPLOT_PATH);

  /**
   * @brief Constructs a TGnuPlotViewer using a TGnuPlotViewerParams object.
   *
   * @param params A structure containing the parameters for GnuPlot
   * visualization.
   */
  TGnuPlotViewer(TGnuPlotViewerParams params);

  /**
   * @brief Default destructor.
   */
  ~TGnuPlotViewer() = default;

  /**
   * @brief Default copy constructor.
   */
  TGnuPlotViewer(const TGnuPlotViewer&) = default;

  /**
   * @brief Default move constructor.
   */
  TGnuPlotViewer(TGnuPlotViewer&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TGnuPlotViewer& operator=(const TGnuPlotViewer&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TGnuPlotViewer& operator=(TGnuPlotViewer&&) noexcept = default;

  /**
   * @brief Retrieves the parameters used for configuring the GnuPlot viewer.
   *
   * @return const TGnuPlotViewerParams& A constant reference to the viewer's
   * parameters.
   */
  [[nodiscard]] const TGnuPlotViewerParams& getParams() const;

  /**
   * @brief Executes the GnuPlot visualization process.
   *
   * This method launches GnuPlot with the configured parameters to visualize
   * the signal data from the specified file.
   */
  void execute() const;

 private:
  TGnuPlotViewerParams _params =
      {};  ///< Parameters for configuring the GnuPlot viewer.
};