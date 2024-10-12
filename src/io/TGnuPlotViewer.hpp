/**
 * @file TGnuPlotViewer.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TFileWriter class, TGnuPlotViewer
 * class, responsible for managing GnuPlot visualizations of signal data.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo Create a method to set up GnuPlot with a single argument (path to
 * GnuPlot). This method should initialize the GnuPlot configuration once and
 * allow reuse across multiple invocations.
 * @todo Simplify and make the constructor more flexible:
 * - Consider a builder pattern to handle optional parameters.
 * - Investigate retrieving information directly from the signal line to
 * configure the viewer automatically.
 * @todo Add option to customize GnuPlot arguments:
 * - Allow passing custom command-line arguments to GnuPlot for increased
 * configurability.
 * @todo Automatic GnuPlot Path Detection.
 * @todo Add functionality to set axis labels based on the signal line:
 * - Enable automatic axis label setting based on the signal line data.
 * - Allow users to choose axis labels when plotting multiple graphs.
 */

#pragma once

#include "TPathManager.hpp"
#include "TSignalLine.hpp"

#include <optional>
#include <string>
#include <vector>

/**
 * @struct TGnuPlotViewerParams
 * @brief Parameters for configuring the GnuPlot viewer.
 */
struct TGnuPlotViewerParams {
    std::vector<std::string>
        filePaths;  ///< Paths to the files with signal data to visualize.
    std::optional<std::vector<std::string>> graphLabels = {
        {SL::DEFAULT_GRAPH_LABEL}};  ///< Label for the graph.
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the X axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the Y axis.
    std::string gnuPlotPath =
        PM::DEFAULT_GNUPLOT_PATH;  ///< Path to the GnuPlot executable.
};

/**
 * @class TGnuPlotViewer
 * @brief Class responsible for visualizing a signal using GnuPlot.
 */
class TGnuPlotViewer {
   public:
    /**
     * @brief Constructs a TGnuPlotViewer with specified parameters.
     *
     * @param filePaths A vector containing paths to the files with signal data.
     * @param graphLabels The labels for the graphs.
     * @param xLabel The label for the X axis.
     * @param yLabel The label for the Y axis.
     * @param gnuPlotPath The path to the GnuPlot executable.
     *
     * @throw SignalProcessingError if the number of files does not match the
     * number of labels.
     */
    explicit TGnuPlotViewer(
        std::vector<std::string>                filePaths,
        std::optional<std::vector<std::string>> graphLabels =
            {{SL::DEFAULT_GRAPH_LABEL}},
        std::optional<std::string> xLabel      = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel      = SL::DEFAULT_Y_LABEL,
        std::string                gnuPlotPath = PM::DEFAULT_GNUPLOT_PATH);

    /**
     * @brief Constructs a TGnuPlotViewer using a TGnuPlotViewerParams object.
     *
     * @param params A structure containing the parameters for GnuPlot
     * visualization.
     *
     * @throw SignalProcessingError if the number of files does not match the
     * number of labels.
     */
    explicit TGnuPlotViewer(TGnuPlotViewerParams params);

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
     * @brief Checks if the visualization process has been executed
     *
     * @return bool True if the visualization process has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the GnuPlot visualization process.
     *
     * @throws SignalProcessingError if the file does not exist.
     */
    void execute() const;

   private:
    TGnuPlotViewerParams _params =
        {};  ///< Parameters for configuring the GnuPlot viewer.
    mutable bool _isExecuted =
        false;  ///< Flag indicating whether the visualization
                ///< process has been executed.
};