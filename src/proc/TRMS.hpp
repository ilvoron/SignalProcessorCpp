/**
 * @file TRMS.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TRMS class for calculating the RMS
 * value (Root Mean Square) of a signal.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo add "do normalization" flag to the parameters.
 */

#pragma once

#include "TSignalLine.hpp"

#include <optional>

/**
 * @struct TRMSParams
 * @brief Contains parameters used for calculating the RMS value of a signal.
 */
struct TRMSParams {
    // Signal Parameters
    const TSignalLine* signalLine = nullptr;  ///< Pointer to the signal line to
    ///< calculate the RMS value.

    // Calculation Parameters
    std::optional<double> inaccuracy =
        SL::DEFAULT_INACCURACY;  ///< Allowed inaccuracy for comparisons.
};

/**
 * @class TRMS
 * @brief Class for calculating the RMS value (Root Mean Square) of a signal.
 */
class TRMS {
   public:
    /**
     * @brief Constructs a TRMS with a signal line.
     *
     * @param signalLine Pointer to the signal line to calculate the RMS value.
     * @param inaccuracy Tolerance for inaccuracy in comparisons.
     */
    explicit TRMS(const TSignalLine*    signalLine,
                  std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY);

    /**
     * @brief Constructs a TRMS with calculation parameters.
     *
     * @param params Structure containing the parameters for RMS calculation.
     */
    explicit TRMS(const TRMSParams& params);

    /**
     * @brief Default destructor.
     */
    ~TRMS() = default;

    /**
     * @brief Default copy constructor.
     */
    TRMS(const TRMS&) = default;

    /**
     * @brief Default move constructor.
     */
    TRMS(TRMS&&) noexcept = default;

    /**
     * @brief Default copy assignment operator.
     */
    TRMS& operator=(const TRMS&) = default;

    /**
     * @brief Default move assignment operator.
     */
    TRMS& operator=(TRMS&&) noexcept = default;

    /**
     * @brief Returns the RMS value of the signal line.
     *
     * @return RMS value of the signal line.
     *
     * @throw SignalProcessingError if the RMS calculation has not been
     * executed.
     */
    [[nodiscard]] double getRMSValue() const;

    /**
     * @brief Returns the parameters used for RMS calculation.
     *
     * @return Parameters used for RMS calculation.
     */
    [[nodiscard]] const TRMSParams& getParams() const;

    /**
     * @brief Returns whether the RMS calculation has been executed.
     *
     * @return True if the RMS calculation has been executed, false otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the RMS calculation.
     *
     * @throw SignalProcessingError if the signal line is not specified or does
     * not have duration information.
     */
    void execute();

   private:
    double     _rmsValue = 0.0;  ///< RMS value of the signal line.
    TRMSParams _params;          ///< Parameters used for RMS calculation.
    bool _isExecuted = false;  ///< Flag indicating whether the RMS calculation
                               ///< has been executed.
};