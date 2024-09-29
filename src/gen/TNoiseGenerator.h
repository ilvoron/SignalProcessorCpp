#pragma once

#include "TSignalLine.h"

#include <cstdint>
#include <memory>
#include <string>

/**
 * @namespace NGEN
 * @brief Contains default parameters used in noise generation.
 */
namespace NGEN {

static constexpr double DEFAULT_NOISE_AMPLITUDE = 1.0;  ///< Default noise
                                                        ///< amplitude.
static const std::string DEFAULT_GRAPH_LABEL =
    "Noisy Signal";  ///< Default graph label.

}  // namespace NGEN

// TODO: Add noise types:
// - `Gaussian`: Generates Gaussian (normal) noise with a specified mean and
// standard deviation.
// - `Pink`: Generates pink noise, which has equal energy per octave (or \(1/f\)
// noise).
// - `Brown`: Generates brown noise (also called red noise), which decreases
// power as \(1/f^2\).
// - `Blue`: Generates blue noise, which increases power as \(f\).
// - `Violet`: Generates violet noise, where power increases as \(f^2\).
// - `Impulse`: Generates impulse noise with random spikes.
/**
 * @enum NoiseType
 * @brief Specifies the types of noise that can be applied to a signal.
 *
 * This enumeration defines various types of noise that can be used in signal
 * processing:
 *
 * - `White`: Generates white noise with uniform random values.
 */
enum class NoiseType : std::uint8_t {
  White  ///< White noise (uniform distribution).
};

/**
 * @struct TNoiseGeneratorParams
 * @brief Parameters for generating a noisy signal line.
 */
struct TNoiseGeneratorParams {
  const TSignalLine* signalLine =
      nullptr;  ///< Pointer to the signal line to add noise to.
  double noiseAmplitude =
      NGEN::DEFAULT_NOISE_AMPLITUDE;  ///< (optional) Amplitude of the noise.
  NoiseType noiseType =
      NoiseType::White;  ///< (optional) Type of noise to apply.
  std::string graphLabel =
      NGEN::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
};

/**
 * @class TNoiseGenerator
 * @brief Class for generating a noisy signal line.
 *
 * The TNoiseGenerator class is responsible for adding noise to an existing
 * signal line. It provides methods to retrieve the noisy signal and its
 * parameters.
 */
class TNoiseGenerator {
 public:
  /**
   * @brief Constructs a TNoiseGenerator with a signal line and noise
   * parameters.
   *
   * @param signalLine Pointer to the signal line to add noise to.
   * @param noiseType (optional) The type of noise to apply.
   * @param graphLabel (optional) Label for the graph.
   */
  TNoiseGenerator(const TSignalLine* signalLine,
                  double noiseAmplitude = NGEN::DEFAULT_NOISE_AMPLITUDE,
                  NoiseType noiseType = NoiseType::White,
                  std::string graphLabel = NGEN::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a TNoiseGenerator with noise generation parameters.
   *
   * @param params Structure containing the parameters for noise generation.
   */
  TNoiseGenerator(TNoiseGeneratorParams params);

  /**
   * @brief Default destructor.
   */
  ~TNoiseGenerator() = default;

  /**
   * @brief Default copy constructor.
   */
  TNoiseGenerator(const TNoiseGenerator&) = default;

  /**
   * @brief Default move constructor.
   */
  TNoiseGenerator(TNoiseGenerator&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TNoiseGenerator& operator=(const TNoiseGenerator&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TNoiseGenerator& operator=(TNoiseGenerator&&) noexcept = default;

  /**
   * @brief Retrieves the noisy signal line.
   *
   * @return const TSignalLine* Pointer to the resulting noisy signal line.
   */
  [[nodiscard]] const TSignalLine* getSignalLine() const;

  /**
   * @brief Retrieves the parameters used for noise generation.
   *
   * @return const TNoiseGeneratorParams& Reference to the noise generation
   * parameters.
   */
  [[nodiscard]] const TNoiseGeneratorParams& getParams() const;

  /**
   * @brief Executes the noise generation process.
   */
  void execute();

 private:
  std::unique_ptr<TSignalLine> _sl =
      nullptr;                         ///< Pointer to the noisy signal line.
  TNoiseGeneratorParams _params = {};  ///< Parameters for noise generation.
};