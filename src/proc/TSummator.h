/**
 * TODO: Sum of two different signals: end summing if one of the signals ends OR
 * add zeros to the end of the shorter signal
 */

#pragma once

#include "TSignalLine.h"

#include <memory>
#include <string>

/**
 * @namespace SUMM
 * @brief Contains default parameters used in signal summation.
 */
namespace SUMM {

static const std::string DEFAULT_GRAPH_LABEL =
    "Summation";  ///< Default graph label.

}  // namespace SUMM

/**
 * @struct TSummatorParams
 * @brief Parameters for summing two signal lines.
 */
struct TSummatorParams {
  const TSignalLine* signalLine1 =
      nullptr;  ///< Pointer to the first signal line.
  const TSignalLine* signalLine2 =
      nullptr;  ///< Pointer to the second signal line.
  double inaccuracy =
      SL::DEFAULT_INACCURACY;  ///< (optional) Allowed inaccuracy for summing
                               ///< the signals
  std::string xLabel =
      SL::DEFAULT_X_LABEL;  ///< (optional) Label for the x-axis.
  std::string yLabel =
      SL::DEFAULT_Y_LABEL;  ///< (optional) Label for the y-axis.
  std::string graphLabel =
      SUMM::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
};

/**
 * @class TSummator
 * @brief Class for summing two signal lines.
 *
 * The TSummator class is responsible for combining two signal lines
 * into one by summing their values on a point-by-point basis.
 */
class TSummator {
 public:
  /**
   * @brief Constructs a TSummator with two signal lines and summation
   * parameters.
   *
   * @param signalLine1 Pointer to the first signal line.
   * @param signalLine2 Pointer to the second signal line.
   * @param inaccuracy (optional) Allowed inaccuracy for summing the signals.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   */
  explicit TSummator(const TSignalLine* signalLine1,
                     const TSignalLine* signalLine2,
                     double inaccuracy = SL::DEFAULT_INACCURACY,
                     std::string xLabel = SL::DEFAULT_X_LABEL,
                     std::string yLabel = SL::DEFAULT_Y_LABEL,
                     std::string graphLabel = SUMM::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a TSummator object using TSummatorParams.
   *
   * @param params A structure containing the parameters for signal summation.
   */
  explicit TSummator(TSummatorParams params);

  /**
   * @brief Default destructor.
   */
  ~TSummator() = default;

  /**
   * @brief Default copy constructor.
   */
  TSummator(const TSummator&) = default;

  /**
   * @brief Default move constructor.
   */
  TSummator(TSummator&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TSummator& operator=(const TSummator&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TSummator& operator=(TSummator&&) noexcept = default;

  /**
   * @brief Retrieves the summed signal line.
   *
   * @return const TSignalLine* Pointer to the resulting summed signal line.
   */
  [[nodiscard]] const TSignalLine* getSignalLine() const;

  /**
   * @brief Retrieves the parameters used for signal summation.
   *
   * @return const TSummatorParams& Reference to the summation parameters.
   */
  [[nodiscard]] const TSummatorParams& getParams() const;

  /**
   * @brief Checks whether the summation has been executed.
   *
   * @return bool True if the summation process has been executed, false
   * otherwise.
   */
  [[nodiscard]] bool isExecuted() const;

  /**
   * @brief Executes the summation of the two signal lines.
   *
   * This method sums values of provided signals on a point-by-point basis
   * according to the parameters and stores the result, which can be retrieved
   * with getSignalLine().
   */
  void execute();

 private:
  std::unique_ptr<TSignalLine> _sl =
      nullptr;                   ///< Pointer to the summed signal line.
  TSummatorParams _params = {};  ///< Parameters for signal summation.
  bool _isExecuted =
      false;  ///< Flag indicating whether the summation has been executed.
};