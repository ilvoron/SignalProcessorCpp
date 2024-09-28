#pragma once

#include "TSignalLine.h"

#include <cstdint>
#include <memory>
#include <string>

/**
 * @namespace DIFF
 * @brief Contains default parameters used in differentiation.
 */
namespace DIFF {

static const std::string DEFAULT_GRAPH_LABEL =
    "Differentiation";  ///< Default graph label.

}  // namespace DIFF

/**
 * @enum DifferentiationMethod
 * @brief Specifies the method to be used for differentiation.
 *
 * This enumeration defines the two possible differentiation methods:
 *
 * - `CentralOnly`: This method applies only central differences for all points.
 *   It reduces the length of the differentiated signal by 2 points compared to
 * the original signal (1 point is removed from the beginning and 1 from the
 * end) since central differences require both a previous and a next point for
 * computation.
 *
 * - `CentralAndEdges`: This method applies central differences to the interior
 * points, but for the first and last points of the signal, it uses one-sided
 * differences (forward difference for the first point, backward difference for
 * the last point). This method maintains the same number of points in the
 * resulting signal as in the original signal, as it doesn't discard the edge
 * points.
 */
enum class DifferentiationMethod : std::uint8_t {
  CentralOnly,  ///< Use only central differences (signal length will be reduced
                ///< by 2 points).
  CentralAndEdges  ///< Use central differences and one-sided at the edges
                   ///< (signal length will remain the same).
};

/**
 * @brief Parameters for differentiating a signal line.
 */
struct TDifferentiatorParams {
  const TSignalLine* signalLine =
      nullptr;  ///< Pointer to the signal line to differentiate.
  std::string xLabel =
      SL::DEFAULT_X_LABEL;  ///< (optional) Label for the x-axis.
  std::string yLabel =
      SL::DEFAULT_Y_LABEL;  ///< (optional) Label for the y-axis.
  std::string graphLabel =
      DIFF::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
  DifferentiationMethod method =
      DifferentiationMethod::CentralAndEdges;  ///< Method for differentiation.
};

class TDifferentiator {
 public:
  /**
   * @brief Constructs a TDifferentiator with a signal line and
   * differentiation parameters.
   *
   * @param signalLine Pointer to the signal line to differentiate.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   * @param method (optional) Method for differentiation: central or central
   * with edge handling.
   */
  TDifferentiator(
      const TSignalLine* signalLine,
      std::string xLabel = SL::DEFAULT_X_LABEL,
      std::string yLabel = SL::DEFAULT_Y_LABEL,
      std::string graphLabel = DIFF::DEFAULT_GRAPH_LABEL,
      DifferentiationMethod method = DifferentiationMethod::CentralAndEdges);

  /**
   * @brief Constructs a TDifferentiator with differentiation parameters.
   *
   * @param params A structure containing the parameters for signal
   * differentiation.
   */
  TDifferentiator(TDifferentiatorParams params);

  /**
   * @brief Default destructor.
   */
  ~TDifferentiator() = default;

  /**
   * @brief Default copy constructor.
   */
  TDifferentiator(const TDifferentiator&) = default;

  /**
   * @brief Default move constructor.
   */
  TDifferentiator(TDifferentiator&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TDifferentiator& operator=(const TDifferentiator&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TDifferentiator& operator=(TDifferentiator&&) noexcept = default;

  /**
   * @brief Retrieves the differentiated signal line.
   *
   * @return const TSignalLine* Pointer to the resulting differentiated signal
   * line.
   */
  [[nodiscard]] const TSignalLine* getSignalLine() const;

  /**
   * @brief Retrieves the parameters used for signal differentiation.
   *
   * @return const TDifferentiatorParams& Reference to the differentiation
   * parameters.
   */
  [[nodiscard]] const TDifferentiatorParams& getParams() const;

  /**
   * @brief Checks whether the differentiation has been executed.
   *
   * @return bool True if the differentiation process has been executed, false
   * otherwise.
   */
  [[nodiscard]] bool isExecuted() const;

  /**
   * @brief Executes the differentiation of the signal line.
   */
  void execute();

 private:
  TDifferentiatorParams _params;  ///< Parameters for signal differentiation.
  std::unique_ptr<TSignalLine>
      _sl;  ///< Pointer to the differentiated signal line.
  bool _isExecuted =
      false;  ///< Indicates if the differentiation has been executed.
};