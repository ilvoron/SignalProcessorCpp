/**
 * @file TFrequencyAnalyzer.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TFrequencyAnalyzer class and related
 * types used for converting signals from the time domain to the frequency
 * domain.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TSignalLine.hpp"

#include <memory>
#include <optional>
#include <string>

/**
 * @namespace FA
 * @brief Contains default parameters used for converting signals from the time
 * domain to the frequency domain.
 */
namespace FA {

    static constexpr bool DEFAULT_USE_ABSOLUTE_VALUE =
        false;  ///< Default flag indicating whether to use the absolute value
                ///< of the correlation.
    static const std::string DEFAULT_GRAPH_LABEL =
        "Fourier Transform";  ///< Default graph label.

}  // namespace FA

/**
 * @struct TFrequencyAnalyzerParams
 * @brief Contains parameters used for converting signals from the
 * time domain to the frequency
 */
struct TFrequencyAnalyzerParams {
    // Signal Parameters
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to transform.

    // Calculation Parameters
    double fromFrequency = 0.0;  ///< Lower bound of the frequency range.
    double toFrequency   = 0.0;  ///< Upper bound of the frequency range.
    double stepFrequency = 0.0;  ///< Step size for the frequency range.
    std::optional<bool> useAbsoluteValue =
        FA::DEFAULT_USE_ABSOLUTE_VALUE;  ///< Flag indicating whether to use the
                                         ///< absolute value of the correlation.

    // Graphical Parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        FA::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TFrequencyAnalyzer
 * @brief Class for converting signals from the time domain to the frequency
 * domain.
 *
 * @note In the resulting frequency domain signal, the x-axis represents the
 * oscillation frequency, while the y-axis represents the correlation value
 * (not amplitude). This analysis does not account for phase shift, so the
 * results indicate only the strength of correlation at each frequency,
 * without providing information about phase differences.
 */
class TFrequencyAnalyzer {
   public:
    /**
     * @brief Constructs a TFrequencyAnalyzer with a signal line and
     * transform parameters.
     *
     * @param signalLine Pointer to the signal line to transform.
     * @param fromFrequency Lower bound of the frequency range.
     * @param toFrequency Upper bound of the frequency range.
     * @param stepFrequency Step size for the frequency range.
     * @param useAbsoluteValue Flag indicating whether to use the absolute value
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     *
     * @throws SignalProcessingError if the frequency range is invalid.
     */
    explicit TFrequencyAnalyzer(
        const TSignalLine*         signalLine,
        double                     fromFrequency    = 0.0,
        double                     toFrequency      = 0.0,
        double                     stepFrequency    = 0.0,
        std::optional<bool>        useAbsoluteValue = false,
        std::optional<std::string> xLabel           = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel           = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel       = FA::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TFrequencyAnalyzer with transform
     * parameters.
     *
     * @param params Structure containing the parameters for signal
     * transformation.
     *
     * @throws SignalProcessingError if the frequency range is invalid.
     */
    explicit TFrequencyAnalyzer(TFrequencyAnalyzerParams params);

    /**
     * @brief Default destructor.
     */
    ~TFrequencyAnalyzer() = default;

    /**
     * @brief Default copy constructor.
     */
    TFrequencyAnalyzer(const TFrequencyAnalyzer& analyzer);

    /**
     * @brief Default move constructor.
     */
    TFrequencyAnalyzer(TFrequencyAnalyzer&&) noexcept = default;

    /**
     * @brief Default copy assignment operator.
     */
    TFrequencyAnalyzer& operator=(const TFrequencyAnalyzer& analyzer);

    /**
     * @brief Default move assignment operator.
     */
    TFrequencyAnalyzer& operator=(TFrequencyAnalyzer&&) noexcept = default;

    /**
     * @brief Retrieves the transformed signal line.
     *
     * @return const TSignalLine* A pointer to the transformed signal line.
     *
     * @throw SignalProcessingError if the Fourier transform has not been
     * executed.
     * @note In the resulting frequency domain signal, the x-axis represents the
     * oscillation frequency, while the y-axis represents the correlation value
     * (not amplitude). This analysis does not account for phase shift, so the
     * results indicate only the strength of correlation at each frequency,
     * without providing information about phase differences.
     */
    [[nodiscard]] const TSignalLine* getSignalLine() const;

    /**
     * @brief Retrieves the parameters of the frequency analyzer.
     *
     * @return const TFrequencyAnalyzerParams& A constant reference
     * to the Fourier transform parameters.
     */
    [[nodiscard]] const TFrequencyAnalyzerParams& getParams() const;

    /**
     * @brief Determines if the frequency analyzer has been executed.
     *
     * @return bool True if the frequency analyzer has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the frequency analyzer to convert the signal from the
     * time domain to the frequency domain.
     *
     * @throws SignalProcessingError if the signal line is null or if the signal
     * line does not contain duration data
     * @note In the resulting frequency domain signal, the x-axis represents the
     * oscillation frequency, while the y-axis represents the correlation value
     * (not amplitude). This analysis does not account for phase shift, so the
     * results indicate only the strength of correlation at each frequency,
     * without providing information about phase differences.
     */
    void execute();

   private:
    std::unique_ptr<TSignalLine> _sl =
        nullptr;  ///< A unique pointer to the transformed signal line.
    TFrequencyAnalyzerParams _params =
        {};                    ///< Parameters of the frequency analyzer.
    bool _isExecuted = false;  ///< Flag indicating if the frequency analyzer
                               ///< has been executed.
};