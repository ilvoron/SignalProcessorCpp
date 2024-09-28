/**
 * TODO: Product of two different signals: end multiplication if one of the
 * signals ends OR add ones (or zeros?) to the end of the shorter signal
 */

#pragma once

#include "TSignalLine.h"

#include <memory>
#include <string>

/**
 * @namespace MULT
 * @brief Contains default parameters used in signal multiplication.
 */
namespace MULT {

static const std::string DEFAULT_GRAPH_LABEL =
    "Multiplication";  ///< Default graph label.

}  // namespace MULT

/**
 * @brief Parameters for multiplying two signal lines.
 */
struct TMultiplierParams {
  const TSignalLine* signalLine1 =
      nullptr;  ///< Pointer to the first signal line.
  const TSignalLine* signalLine2 =
      nullptr;  ///< Pointer to the second signal line.
  double inaccuracy =
      SL::DEFAULT_INACCURACY;  ///< (optional) Allowed inaccuracy for
                               ///< multiplying the signals
  std::string xLabel =
      SL::DEFAULT_X_LABEL;  ///< (optional) Label for the x-axis.
  std::string yLabel =
      SL::DEFAULT_Y_LABEL;  ///< (optional) Label for the y-axis.
  std::string graphLabel =
      MULT::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
};

/**
 * @class TMultiplier
 * @brief Class for multiplying two signal lines.
 *
 * The TMultiplier class is responsible for combining two signal lines
 * into one by multiplying their values on a point-by-point basis.
 */
class TMultiplier {
 public:
  /**
   * @brief Constructs a TMultiplier with two signal lines and multiplication
   * parameters.
   *
   * @param signalLine1 Pointer to the first signal line.
   * @param signalLine2 Pointer to the second signal line.
   * @param inaccuracy (optional) Allowed inaccuracy for multiplying the
   * signals.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   */
  TMultiplier(const TSignalLine* signalLine1,
              const TSignalLine* signalLine2,
              double inaccuracy = SL::DEFAULT_INACCURACY,
              std::string xLabel = SL::DEFAULT_X_LABEL,
              std::string yLabel = SL::DEFAULT_Y_LABEL,
              std::string graphLabel = MULT::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a TMultiplier object using TMultiplierParams.
   *
   * @param params A structure containing the parameters for signal
   * multiplication.
   */
  TMultiplier(TMultiplierParams params);

  /**
   * @brief Default destructor.
   */
  ~TMultiplier() = default;

  /**
   * @brief Default copy constructor.
   */
  TMultiplier(const TMultiplier&) = default;

  /**
   * @brief Default move constructor.
   */
  TMultiplier(TMultiplier&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TMultiplier& operator=(const TMultiplier&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TMultiplier& operator=(TMultiplier&&) noexcept = default;

  /**
   * @brief Retrieves the multiplied signal line.
   *
   * @return const TSignalLine* Pointer to the resulting multiplied signal line.
   */
  [[nodiscard]] const TSignalLine* getSignalLine() const;

  /**
   * @brief Retrieves the parameters used for signal multiplication.
   *
   * @return const TMultiplierParams& Reference to the multiplication
   * parameters.
   */
  [[nodiscard]] const TMultiplierParams& getParams() const;

  /**
   * @brief Checks whether the multiplication has been executed.
   *
   * @return bool True if the multiplication process has been executed, false
   * otherwise.
   */
  [[nodiscard]] bool isExecuted() const;

  /**
   * @brief Executes the multiplication of the two signal lines.
   *
   * This method multiplies values of provided signals on a point-by-point basis
   * according to the parameters and stores the result, which can be retrieved
   * with getSignalLine().
   */
  void execute();

 private:
  std::unique_ptr<TSignalLine> _sl =
      nullptr;                     ///< Pointer to the multiplied signal line.
  TMultiplierParams _params = {};  ///< Parameters for signal multiplication.
  bool _isExecuted =
      false;  ///< Flag indicating whether the multiplication has been executed.
};