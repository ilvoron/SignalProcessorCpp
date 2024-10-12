/**
 * @file TGenerator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TGenerator class for signal waveform
 * generation.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo Add soft clamping
 * @todo Add antialiasing warnings (Nyquist frequency)
 */

#pragma once

#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

/**
 * @namespace GEN
 * @brief Contains default parameters values for signal parameters.
 */
namespace GEN {

    /**
     * @enum GenerationMethod
     * @brief Specifies the method used for generating a signal.
     *
     * @details This enum defines the available methods for generating different
     * types of signals. Each waveform type is based on a trigonometric
     * function, allowing the user to select from various shapes that exhibit
     * periodic behavior.
     *
     * - **SineWave**: Generates a smooth, periodic sine wave, which oscillates
     *   between -amplitude and +amplitude. This waveform starts from the origin
     *   and follows the pattern of sin(x).
     *
     * - **CosineWave**: Generates a smooth periodic cosine wave, which also
     * oscillates between -amplitude and +amplitude. This waveform starts from
     * the maximum amplitude and follows the pattern of cos(x).
     *
     * - **TangentWave**: Generates a periodic tangent wave with vertical
     * asymptotes. This waveform repeats its pattern with sharp rises and falls
     * as it approaches points where the tangent function goes to infinity. The
     * `y` values are clamped to prevent extreme values, and `offsetY` is
     * applied after clamping.
     *
     * - **CotangentWave**: Generates a periodic cotangent wave, which also has
     * vertical asymptotes similar to the tangent wave. It mirrors the tangent
     * wave but starts from infinity at the origin and decreases. The `y` values
     * are clamped, and `offsetY` is applied after clamping to ensure stable and
     * manageable output values.
     *
     * @note For **TangentWave** and **CotangentWave**, due to the presence of
     * vertical asymptotes, the generated values are clamped to a specified
     * range before applying `offsetY`. This prevents large spikes in the signal
     * which may disrupt the graph rendering.
     */
    enum class GenerationMethod : std::uint8_t {
        SineWave,      ///< Generates a sine wave signal.
        CosineWave,    ///< Generates a cosine wave signal.
        TangentWave,   ///< Generates a tangent wave signal.
        CotangentWave  ///< Generates a cotangent wave signal.
    };

    // Graphical parameters
    static const std::string DEFAULT_X_LABEL =
        "Time";  ///< Default label for the x-axis.
    static const std::string DEFAULT_Y_LABEL =
        "Amplitude";  ///< Default label for the y-axis.
    static const std::string DEFAULT_GRAPH_LABEL =
        "Signal";  ///< Default label for the graph.

    // Generation parameters
    static constexpr double DEFAULT_NORMALIZE_FACTOR_SIN =
        TWO_PI;  ///< Default normalization factor applied to sinus wave
                 ///< signals. See @ref TSignalLineParams::normalizeFactor
                 ///< "normalizeFactor" in TSignalLineParams for more
                 ///< information.
    static constexpr auto DEFAULT_GEN_METHOD =
        GenerationMethod::SineWave;  ///< Default method for generating the
                                     ///< signal.
    static constexpr double DEFAULT_CLAMP_VALUE =
        10.0;  ///< Default value for clamping the signal amplitude.

}  // namespace GEN

/**
 * @struct TGeneratorParams
 * @brief Contains parameters for generating a signal line.
 *
 * @note Some parameters are optional and represented by std::optional. These
 * can be set by the user or remain unset, in which case default values or
 * behaviors are applied.
 */
struct TGeneratorParams {
    // Signal parameters
    double samplingFreq =
        SL::DEFAULT_SAMPLING_FREQ_HZ;  ///< Sampling frequency of the signal, in
                                       ///< Hz.
    double duration =
        SL::DEFAULT_DURATION_SECONDS;  ///< Duration of the signal, in seconds.
    double oscillationFreq =
        SL::DEFAULT_FREQ_HZ;  ///< Oscillation frequency of the signal, in Hz.
    double initPhase =
        SL::DEFAULT_INIT_PHASE;             ///< Initial phase of the signal.
    double offsetY = SL::DEFAULT_OFFSET_Y;  ///< Vertical offset of the signal.
    double amplitude = SL::DEFAULT_AMPLITUDE;  ///< Amplitude of the signal.

    // Generation parameters
    GEN::GenerationMethod method =
        GEN::DEFAULT_GEN_METHOD;  ///< Method for generating the signal.
    std::optional<double> clampValue =
        GEN::DEFAULT_CLAMP_VALUE;  ///< Clamping value for the signal amplitude.

    // Graphical parameters
    std::optional<std::string> xLabel =
        GEN::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        GEN::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        GEN::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TGenerator
 * @brief Class for generating a signal line with specified parameters.
 */
class TGenerator {
   public:
    /**
     * @brief Constructs a TGenerator with specified signal parameters.
     *
     * @param samplingFrequency The sampling frequency of the signal.
     * @param duration The total duration of the signal.
     * @param oscillationFrequency The oscillation frequency of the
     * signal.
     * @param initPhase The initial phase of the signal.
     * @param offsetY The vertical offset of the signal.
     * @param amplitude The amplitude of the signal.
     * @param method The method used for generating the signal.
     * @param clampValue The clamping value for the signal amplitude.
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     *
     * @throws SignalProcessingError if the clamp value is not specified or
     * positive for tangent and cotangent waveforms.
     */
    explicit TGenerator(
        double samplingFrequency            = SL::DEFAULT_SAMPLING_FREQ_HZ,
        double duration                = SL::DEFAULT_DURATION_SECONDS,
        double oscillationFrequency                    = SL::DEFAULT_FREQ_HZ,
        double initPhase                      = SL::DEFAULT_INIT_PHASE,
        double offsetY                        = SL::DEFAULT_OFFSET_Y,
        double amplitude                      = SL::DEFAULT_AMPLITUDE,
        GEN::GenerationMethod      method     = GEN::DEFAULT_GEN_METHOD,
        std::optional<double>      clampValue = GEN::DEFAULT_CLAMP_VALUE,
        std::optional<std::string> xLabel     = GEN::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel     = GEN::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = GEN::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TGenerator using a TGeneratorParams object.
     *
     * @param params A structure containing the parameters for the signal
     * generation.
     *
     * @throws SignalProcessingError if the clamp value is not specified or
     * positive for tangent and cotangent waveforms.
     */
    explicit TGenerator(TGeneratorParams params);

    /**
     * @brief Default destructor.
     */
    ~TGenerator() = default;

    /**
     * @brief Copy constructor.
     *
     * @param generator A constant reference to the generator to copy.
     */
    TGenerator(const TGenerator& generator);

    /**
     * @brief Default move constructor.
     */
    TGenerator(TGenerator&&) noexcept = default;

    /**
     * @brief Copy assignment operator.
     *
     * @param generator A constant reference to the generator to copy.
     */
    TGenerator& operator=(const TGenerator& generator);

    /**
     * @brief Default move assignment operator.
     */
    TGenerator& operator=(TGenerator&&) noexcept = default;

    /**
     * @brief Retrieves a pointer to the generated signal line.
     *
     * @return const TSignalLine* A pointer to the generated signal line.
     *
     * @throws SignalProcessingError if the signal line is not generated.
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
     * @details The generation process varies based on the selected waveform
     * type (sine, cosine, tangent, cotangent), and the resulting signal is
     * stored internally and can be accessed with `getSignalLine()`.
     *
     * @note For tangent and cotangent waves, any extreme values are clamped to
     * maintain stability, and `offsetY` is applied to adjust the vertical
     * position of the signal. This process may throw exceptions if any
     * required parameters are missing or invalid.
     *
     * @throws SignalProcessingError if the signal generation fails due to
     * invalid parameters or configuration.
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