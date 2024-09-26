#pragma once
#include "TSignalLine.h"
#include <memory>

// TODO: Sum of two different signals: end summing if one of the signals ends OR add zeros to the end of the shorter signal

/**
 * @brief Parameters for summing two signal lines.
 */
struct TSummatorParams {
	const TSignalLine* signalLine1 = nullptr; ///< Pointer to the first signal line.
	const TSignalLine* signalLine2 = nullptr; ///< Pointer to the second signal line.
	double inaccuracy = 0.05;                 ///< Allowed inaccuracy for summing the signals (default: 0.05).
	std::string xLabel = "X Axis";            ///< Label for the x-axis (default: "X Axis").
	std::string yLabel = "Y Axis";            ///< Label for the y-axis (default: "Y Axis").
	std::string graphLabel = "Summation";     ///< Label for the graph (default: "Summation").
};

/**
 * @class TSummator
 * @brief Class for summing two signal lines.
 * 
 * The TSummator class is responsible for combining two signal lines
 * into one by summing their values on a point-by-point basis.
 */
class TSummator{
	public:
		/**
		 * @brief Constructs a TSummator with two signal lines and summation parameters.
		 * 
		 * @param signalLine1 Pointer to the first signal line.
		 * @param signalLine2 Pointer to the second signal line.
		 * @param inaccuracy Allowed inaccuracy for summing the signals (optional, default: 0.05).
		 * @param xLabel Label for the x-axis (optional, default: "X Axis").
		 * @param yLabel Label for the y-axis (optional, default: "Y Axis").
		 * @param graphLabel Label for the graph (optional, default: "Summation").
		 */
		TSummator(const TSignalLine* signalLine1,
		          const TSignalLine* signalLine2,
		          double inaccuracy = 0.05,
		          std::string xLabel = "X Axis",
		          std::string yLabel = "Y Axis",
		          std::string graphLabel = "Summation");

		/**
		 * @brief Constructs a TSummator object using TSummatorParams.
		 * 
		 * @param params A structure containing the parameters for signal summation.
		 */
		TSummator(TSummatorParams params);

		/**
		 * @brief Default destructor.
		 */
		~TSummator() = default;

		/**
		 * @brief Retrieves the summed signal line.
		 * 
		 * @return const TSignalLine* Pointer to the resulting summed signal line.
		 */
		const TSignalLine* getSignalLine() const;

		/**
		 * @brief Retrieves the parameters used for signal summation.
		 * 
		 * @return const TSummatorParams& Reference to the summation parameters.
		 */
		const TSummatorParams& getParams() const;

		/**
		 * @brief Checks whether the summation has been executed.
		 * 
		 * @return bool True if the summation process has been executed, false otherwise.
		 */
		bool isExecuted() const;

		/**
		 * @brief Executes the summation of the two signal lines.
		 * 
		 * This method sums values of provided signals on a point-by-point basis according
		 * to the parameters and stores the result, which can be retrieved with getSignalLine().
		 */
		void execute();
	private:
		std::unique_ptr<TSignalLine> _sl = nullptr; ///< Pointer to the summed signal line.
		TSummatorParams _params = {};               ///< Parameters for signal summation.
		bool _isExecuted = false;                   ///< Flag indicating whether the summation has been executed.
};