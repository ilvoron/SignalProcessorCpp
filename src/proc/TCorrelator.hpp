/**
 * @file TCorrelator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TCorrelator class correlating
 * two signal lines generation.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TSignalLine.hpp"

#include <optional>

/**
 * @namespace COR
 * @brief Contains default parameters used for correlating two signal lines.
 */
namespace COR {

    static constexpr bool DEFAULT_PERFORM_NORMALIZATION =
        true;  ///< Default flag indicating whether to normalize the signal
               ///< lines.

}  // namespace COR

/**
 * @struct TCorrelatorParams
 * @brief Contains parameters used for correlating two signal lines.
 */
struct TCorrelatorParams {
    // Signal Parameters
    const TSignalLine* signalLine1 =
        nullptr;  ///< Pointer to the first signal line to correlate.
    const TSignalLine* signalLine2 =
        nullptr;  ///< Pointer to the second signal line to correlate.

    // Calculation Parameters
    std::optional<bool> performNormalization =
        COR::DEFAULT_PERFORM_NORMALIZATION;  ///< Flag indicating whether to
                                             ///< normalize the signal lines.
};

/**
 * @class TCorrelator
 * @brief Class for correlating two signal lines.
 *
 * @note This correlation analysis measures only the magnitude of the
 * relationship between the two signals at each frequency. It does not account
 * for any phase shifts, meaning that the results reflect only the strength of
 * the correlation and do not provide information about phase differences
 * between the signals.
 */
class TCorrelator {
   public:
    /**
     * @brief Constructs a TCorrelator with two signal lines.
     *
     * @param signalLine1 Pointer to the first signal line to correlate.
     * @param signalLine2 Pointer to the second signal line to correlate.
     * @param performNormalization Flag indicating whether to normalize the
     * signal lines.
     */
    TCorrelator(const TSignalLine*  signalLine1,
                const TSignalLine*  signalLine2,
                std::optional<bool> performNormalization = true);

    /**
     * @brief Constructs a TCorrelator with correlation parameters.
     *
     * @param params Structure containing the parameters for correlation.
     */
    explicit TCorrelator(const TCorrelatorParams& params);

    /**
     * @brief Default destructor.
     */
    ~TCorrelator() = default;

    /**
     * @brief Default copy constructor.
     */
    TCorrelator(const TCorrelator&) = default;

    /**
     * @brief Default move constructor.
     */
    TCorrelator(TCorrelator&&) noexcept = default;

    /**
     * @brief Default copy assignment operator.
     */
    TCorrelator& operator=(const TCorrelator&) = default;

    /**
     * @brief Default move assignment operator.
     */
    TCorrelator& operator=(TCorrelator&&) noexcept = default;

    /**
     * @brief Retrieves the correlation value between the two signal lines.
     *
     * @return double The correlation value.
     *
     * @throw SignalProcessingError If the correlation has not been executed
     * yet.
     * @note This correlation analysis measures only the magnitude of the
     * relationship between the two signals at each frequency. It does not
     * account for any phase shifts, meaning that the results reflect only the
     * strength of the correlation and do not provide information about phase
     * differences between the signals.
     */
    [[nodiscard]] double getCorrelationValue() const;

    /**
     * @brief Retrieves the parameters used for correlation.
     *
     * @return const TCorrelator& A constant reference to the correlation
     * parameters.
     */
    [[nodiscard]] const TCorrelatorParams& getParams() const;

    /**
     * @brief Checks whether the correlation has been executed.
     *
     * @return true If the correlation has been executed.
     * @return false Otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the correlation between the two signal lines.
     *
     * @throw SignalProcessingError If one of the signal lines is invalid or if
     * the signal lines do not have duration information.
     * @note This correlation analysis measures only the magnitude of the
     * relationship between the two signals at each frequency. It does not
     * account for any phase shifts, meaning that the results reflect only the
     * strength of the correlation and do not provide information about phase
     * differences between the signals.
     */
    void execute();

   private:
    double _correlationValue = 0.0;  ///< The correlation value between the two
    ///< signal lines.
    TCorrelatorParams _params = {};  ///< Parameters used for correlation.

    bool _isExecuted = false;  ///< Flag indicating if the correlation has
                               ///< been executed.
};