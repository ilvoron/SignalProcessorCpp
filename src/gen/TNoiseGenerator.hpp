/**
 * @file TNoiseGenerator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TNoiseGenerator class and supporting
 * structures for adding noise to signal lines.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TSignalLine.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

/**
 * @namespace NGEN
 * @brief Contains default parameters used in noise generation.
 */
namespace NGEN {

    /**
     * @enum NoiseType
     * @brief Specifies the types of noise that can be applied to a signal.
     *
     * This enumeration defines various types of noise that can be used in
     * signal processing:
     *
     * - `White`: Generates white noise with uniform random values.
     *
     * @todo Add noise types:
     * - `Gaussian`: Generates Gaussian (normal) noise with a specified mean and
     * standard deviation.
     * - `Pink`: Generates pink noise, which has equal energy per octave (or
     * \(1/f\) noise).
     * - `Brown`: Generates brown noise (also called red noise), which decreases
     *  power as \(1/f^2\).
     * - `Blue`: Generates blue noise, which increases power as \(f\).
     * - `Violet`: Generates violet noise, where power increases as \(f^2\).
     * - `Impulse`: Generates impulse noise with random spikes.
     */
    enum class NoiseType : std::uint8_t {
        White  ///< White noise (uniform distribution).
    };

    // Graphical parameters
    static const std::string DEFAULT_GRAPH_LABEL =
        "Noisy Signal";  ///< Default graph label.

    // Generation parameters
    static constexpr double DEFAULT_NOISE_AMPLITUDE = 1.0;  ///< Default noise
                                                            ///< amplitude.
    static constexpr auto DEFAULT_NOISE_TYPE =
        NoiseType::White;  ///< Default noise type.

}  // namespace NGEN

/**
 * @struct TNoiseGeneratorParams
 * @brief Parameters for generating a noisy signal line.
 *
 * @note Some parameters are optional and represented by std::optional. These
 * can be set by the user or remain unset, in which case default values or
 * behaviors are applied.
 */
struct TNoiseGeneratorParams {
    // Signal parameters
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to add noise to.

    // Noise parameters
    double noiseAmplitude =
        NGEN::DEFAULT_NOISE_AMPLITUDE;  ///< Amplitude of the noise.
    NGEN::NoiseType noiseType =
        NGEN::DEFAULT_NOISE_TYPE;  ///< Type of noise to apply.

    // Graphical parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        NGEN::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TNoiseGenerator
 * @brief Class for generating a noisy signal line.
 */
class TNoiseGenerator {
   public:
    /**
     * @brief Constructs a TNoiseGenerator with a signal line and noise
     * parameters.
     *
     * @param signalLine Pointer to the signal line to add noise to.
     * @param noiseAmplitude The amplitude of the noise.
     * @param noiseType The type of noise to apply.
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     */
    explicit TNoiseGenerator(
        const TSignalLine* signalLine,
        double             noiseAmplitude     = NGEN::DEFAULT_NOISE_AMPLITUDE,
        NGEN::NoiseType    noiseType          = NGEN::NoiseType::White,
        std::optional<std::string> xLabel     = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel     = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = NGEN::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TNoiseGenerator with noise generation parameters.
     *
     * @param params Structure containing the parameters for noise generation.
     */
    explicit TNoiseGenerator(TNoiseGeneratorParams params);

    /**
     * @brief Default destructor.
     */
    ~TNoiseGenerator() = default;

    /**
     * @brief Copy constructor.
     */
    TNoiseGenerator(const TNoiseGenerator& generator);

    /**
     * @brief Default move constructor.
     */
    TNoiseGenerator(TNoiseGenerator&&) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    TNoiseGenerator& operator=(const TNoiseGenerator& generator);

    /**
     * @brief Default move assignment operator.
     */
    TNoiseGenerator& operator=(TNoiseGenerator&&) noexcept = default;

    /**
     * @brief Retrieves the noisy signal line.
     *
     * @return const TSignalLine* Pointer to the resulting noisy signal line.
     *
     * @throws SignalProcessingError if the noise generation process is not
     * executed.
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
     * @brief Checks if the noise generation process is executed.
     *
     * @return bool True if the noise generation is executed, false otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the noise generation process.
     *
     * @throws SignalProcessingError if the signal line is not set.
     */
    void execute();

   private:
    std::unique_ptr<TSignalLine> _sl =
        nullptr;                         ///< Pointer to the noisy signal line.
    TNoiseGeneratorParams _params = {};  ///< Parameters for noise generation.
    bool                  _isExecuted =
        false;  ///< Flag indicating if the noise generation is executed.
};