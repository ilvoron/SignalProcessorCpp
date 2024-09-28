#pragma once

#include "TSignalLine.h"

#include <memory>

/**
 * @namespace GEN
 * @brief Contains default parameters used in signal generation.
 */
namespace GEN {

static const std::string DEFAULT_X_LABEL = "Time";  ///< Default x-axis label.
static const std::string DEFAULT_Y_LABEL =
    "Amplitude";  ///< Default y-axis label.
static const std::string DEFAULT_GRAPH_LABEL =
    "Signal";  ///< Default graph label.

}  // namespace GEN

/**
 * @brief Parameters for generating a signal line.
 */
struct TGeneratorParams {
  double time = SL::DEFAULT_TIME;  ///< (optional)
                                   ///< Total time duration.
  double oscillationFreq =
      SL::DEFAULT_OSCILLATION_FREQ;                  ///< (optional)
                                                     ///< Oscillation frequency.
  double initPhase = SL::DEFAULT_INIT_PHASE;         ///< (optional)
                                                     ///< Initial phase.
  double offsetY = SL::DEFAULT_OFFSET_Y;             ///< (optional)
                                                     ///< Vertical offset.
  double amplitude = SL::DEFAULT_AMPLITUDE;          ///< (optional)
                                                     ///< Amplitude.
  double samplingFreq = SL::DEFAULT_SAMPLING_FREQ;   ///< (optional)
                                                     ///< Sampling frequency.
  std::string xLabel = SL::DEFAULT_X_LABEL;          ///< (optional)
                                                     ///< Label for the x-axis.
  std::string yLabel = SL::DEFAULT_Y_LABEL;          ///< (optional)
                                                     ///< Label for the y-axis.
  std::string graphLabel = SL::DEFAULT_GRAPH_LABEL;  ///< (optional)
                                                     ///< Label for the graph.
};

/**
 * @class TGenerator
 * @brief Class for generating a signal line with specified parameters.
 *
 * This class allows for the generation of a signal line based on configurable
 * parameters. It provides methods to retrieve the generated signal and its
 * parameters.
 */
class TGenerator {
 public:
  /**
   * @brief Constructs a TGenerator with specified signal parameters (aka "full
   * generator").
   *
   * @param time (optional) The total time duration of the signal.
   * @param oscillationFreq (optional) The oscillation frequency of the signal.
   * @param initPhase (optional) The initial phase of the signal.
   * @param offsetY (optional) The vertical offset of the signal.
   * @param amplitude (optional) The amplitude of the signal.
   * @param samplingFreq (optional) The sampling frequency of the signal.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   */
  TGenerator(double time = SL::DEFAULT_TIME,
             double oscillationFreq = SL::DEFAULT_OSCILLATION_FREQ,
             double initPhase = SL::DEFAULT_INIT_PHASE,
             double offsetY = SL::DEFAULT_OFFSET_Y,
             double amplitude = SL::DEFAULT_AMPLITUDE,
             double samplingFreq = SL::DEFAULT_SAMPLING_FREQ,
             std::string xLabel = GEN::DEFAULT_X_LABEL,
             std::string yLabel = GEN::DEFAULT_Y_LABEL,
             std::string graphLabel = GEN::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a TGenerator using a TGeneratorParams object.
   *
   * @param params A structure containing the parameters for the signal
   * generation.
   */
  TGenerator(TGeneratorParams params);

  /**
   * @brief Default destructor.
   */
  ~TGenerator() = default;

  /**
   * @brief Default copy constructor.
   */
  TGenerator(const TGenerator&) = default;

  /**
   * @brief Default move constructor.
   */
  TGenerator(TGenerator&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TGenerator& operator=(const TGenerator&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TGenerator& operator=(TGenerator&&) noexcept = default;

  /**
   * @brief Retrieves a pointer to the generated signal line.
   *
   * @return const TSignalLine* A pointer to the generated signal line.
   */
  [[nodiscard]] const TSignalLine* getSignalLine() const;

  /**
   * @brief Retrieves the parameters used for signal generation.
   *
   * @return const TGeneratorParams& A constant reference to the signal
   * generation parameters.
   */
  [[nodiscard]] const TGeneratorParams& getParams() const;

  /**
   * @brief Checks if the signal has been generated.
   *
   * @return bool True if the signal has been generated, false otherwise.
   */
  [[nodiscard]] bool isExecuted() const;

  /**
   * @brief Executes the signal generation process.
   *
   * This method generates the signal line based on the current parameters.
   * Once executed, the signal can be accessed through getSignalLine().
   */
  void execute();

 private:
  std::unique_ptr<TSignalLine> _sl =
      nullptr;  ///< A unique pointer to the generated signal line.
  TGeneratorParams _params =
      {};  ///< Parameters for generating the signal line.
  bool _isExecuted =
      false;  ///< Flag indicating whether the signal has been generated.
};