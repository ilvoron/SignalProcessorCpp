#pragma once

#include "TSignalLine.h"

#include <memory>

/**
 * @namespace AD
 * @brief Contains default parameters used for amplitude detection.
 */
namespace AD {

static constexpr double DEFAULT_INACCURACY =
    0.05;  ///< Default tolerance for inaccuracy in comparisons.

}  // namespace AD

/**
 * @struct TAmplitudeDetectorParams
 * @brief Contains parameters used for detecting the amplitude of a signal.
 */
struct TAmplitudeDetectorParams {
  const TSignalLine* signalLine =
      nullptr;  ///< Pointer to the signal line to detect the amplitude.
};

/**
 * @class TAmplitudeDetector
 * @brief Class for detecting the amplitude of a signal line.
 */
class TAmplitudeDetector {
 public:
  /**
   * @brief Constructs a TAmplitudeDetector with a signal line.
   *
   * @param signalLine Pointer to the signal line to detect the amplitude.
   */
  explicit TAmplitudeDetector(const TSignalLine* signalLine);

  /**
   * @brief Constructs a TAmplitudeDetector with detection parameters.
   *
   * @param params Structure containing the parameters for amplitude detection.
   */
  explicit TAmplitudeDetector(TAmplitudeDetectorParams params);

  /**
   * @brief Default destructor.
   */
  ~TAmplitudeDetector() = default;

  /**
   * @brief Default copy constructor.
   */
  TAmplitudeDetector(const TAmplitudeDetector&) = default;

  /**
   * @brief Default move constructor.
   */
  TAmplitudeDetector(TAmplitudeDetector&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TAmplitudeDetector& operator=(const TAmplitudeDetector&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TAmplitudeDetector& operator=(TAmplitudeDetector&&) noexcept = default;

  /**
   * @brief Retrieves the detected amplitude.
   *
   * @return double Detected amplitude of the signal.
   */
  [[nodiscard]] double getAmplitude() const;

  /**
   * @brief Retrieves the parameters used for amplitude detection.
   *
   * @return const TAmplitudeDetectorParams& Reference to the detection
   * parameters.
   */
  [[nodiscard]] const TAmplitudeDetectorParams& getParams() const;

  /**
   * @brief Checks whether the amplitude detection has been executed.
   *
   * @return bool True if the amplitude detection process has been executed,
   * false otherwise.
   */
  [[nodiscard]] bool isExecuted() const;

  /**
   * @brief Executes the detection of the amplitude of the signal line.
   *
   * @param normalizationInaccuracy Tolerance for inaccuracy in comparisons.
   */
  void execute(double normalizationInaccuracy = AD::DEFAULT_INACCURACY);

 private:
  std::unique_ptr<TSignalLine> _normalizedSignalLine =
      nullptr;                       ///< Normalized signal line.
  TAmplitudeDetectorParams _params;  ///< Parameters for amplitude detection.
  double _amplitude = 0.0;           ///< Detected amplitude of the signal.
  bool _isExecuted =
      false;  ///< Flag indicating whether the detection has been executed.
};