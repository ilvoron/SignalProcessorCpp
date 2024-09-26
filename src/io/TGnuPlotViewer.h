#pragma once
#include <string>

/**
 * @brief Parameters for configuring the GnuPlot viewer.
 * 
 * This structure contains the parameters needed to plot a signal using GnuPlot.
 */
struct TGnuPlotViewerParams {
	const std::string& filePath = "";           ///< Path to the file containing the signal data (default: "").
	const std::string& gnuPlotPath = "gnuplot"; ///< Path to the GnuPlot executable (default: "gnuplot").
	const std::string& xLabel = "X axis";       ///< Label for the X axis (default: "X axis").
	const std::string& yLabel = "Y axis";       ///< Label for the Y axis (default: "Y axis").
	const std::string& graphLabel = "Graph";    ///< Label for the graph (default: "Graph").
};

/**
 * @class TGnuPlotViewer
 * @brief Class responsible for visualizing a signal using GnuPlot.
 * 
 * This class allows plotting a signal stored in a file using the GnuPlot tool.
 * It is configurable through a set of parameters including the file path, GnuPlot path, and axis labels.
 */
class TGnuPlotViewer {
	public:
		/**
		 * @brief Constructs a TGnuPlotViewer with specified parameters.
		 * 
		 * @param filePath The path to the file containing the signal data.
		 * @param gnuPlotPath The path to the GnuPlot executable (default: "gnuplot").
		 * @param xLabel The label for the X axis (default: "X axis").
		 * @param yLabel The label for the Y axis (default: "Y axis").
		 * @param graphLabel The label for the graph (default: "Graph").
		 */
		TGnuPlotViewer(const std::string& filePath,
		               const std::string& gnuPlotPath = "gnuplot",
		               const std::string& xLabel = "X axis",
		               const std::string& yLabel = "Y axis",
		               const std::string& graphLabel = "Graph");

		/**
		 * @brief Constructs a TGnuPlotViewer using a TGnuPlotViewerParams object.
		 * 
		 * @param params A structure containing the parameters for GnuPlot visualization.
		 */
		TGnuPlotViewer(TGnuPlotViewerParams params);

		/**
		 * @brief Destructor for the TGnuPlotViewer object.
		 * 
		 * Default destructor as no custom resource management is required.
		 */
		~TGnuPlotViewer() = default;

		/**
		 * @brief Retrieves the parameters used for configuring the GnuPlot viewer.
		 * 
		 * @return const TGnuPlotViewerParams& A constant reference to the viewer's parameters.
		 */
		const TGnuPlotViewerParams& getParams() const;

		/**
		 * @brief Executes the GnuPlot visualization process.
		 * 
		 * This method launches GnuPlot with the configured parameters to visualize
		 * the signal data from the specified file.
		 */
		void execute();
	private:
		TGnuPlotViewerParams _params = {}; ///< Parameters for configuring the GnuPlot viewer.
};