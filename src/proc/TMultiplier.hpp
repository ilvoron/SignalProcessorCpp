/**
 * @file TMultiplier.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TMultiplier class and its associated
 * parameters for multiplying two signal lines.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo Product of two different signals: end multiplication if one of the
 * signals ends OR add ones (or zeros?) to the end of the shorter signal
 */

#pragma once

#include "TSignalLine.hpp"

#include <memory>
#include <optional>
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
 * @struct TMultiplierParams
 * @brief Parameters for multiplying two signal lines.
 */
struct TMultiplierParams {
    // Signal parameters
    const TSignalLine* signalLine1 =
        nullptr;  ///< Pointer to the first signal line.
    const TSignalLine* signalLine2 =
        nullptr;  ///< Pointer to the second signal line.

    // Multiplication parameters
    std::optional<double> inaccuracy =
        SL::DEFAULT_INACCURACY;  ///< Allowed inaccuracy for
    ///< summing the signals

    // Graphical parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        MULT::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TMultiplier
 * @brief Class for multiplying two signal lines into one by multiplying their
 * values on a point-by-point basis.
 */
class TMultiplier {
   public:
    /**
     * @brief Constructs a TMultiplier with two signal lines and multiplication
     * parameters.
     *
     * @param signalLine1 Pointer to the first signal line.
     * @param signalLine2 Pointer to the second signal line.
     * @param inaccuracy Allowed inaccuracy for multiplying the
     * signals.
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     */
    explicit TMultiplier(
        const TSignalLine*          signalLine1,
        const TSignalLine*          signalLine2,
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY,
        std::optional<std::string>  xLabel     = SL::DEFAULT_X_LABEL,
        std::optional<std::string>  yLabel     = SL::DEFAULT_Y_LABEL,
        std::optional<std::string>  graphLabel = MULT::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TMultiplier object using TMultiplierParams.
     *
     * @param params A structure containing the parameters for signal
     * multiplication.
     */
    explicit TMultiplier(TMultiplierParams params);

    /**
     * @brief Default destructor.
     */
    ~TMultiplier() = default;

    /**
     * @brief Copy constructor.
     */
    TMultiplier(const TMultiplier& multiplier);

    /**
     * @brief Default move constructor.
     */
    TMultiplier(TMultiplier&&) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    TMultiplier& operator=(const TMultiplier& multiplier);

    /**
     * @brief Default move assignment operator.
     */
    TMultiplier& operator=(TMultiplier&&) noexcept = default;

    /**
     * @brief Retrieves the multiplied signal line.
     *
     * @return const TSignalLine* Pointer to the resulting multiplied signal
     * line.
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
     */
    void execute();

   private:
    std::unique_ptr<TSignalLine> _sl =
        nullptr;                     ///< Pointer to the multiplied signal line.
    TMultiplierParams _params = {};  ///< Parameters for signal multiplication.
    bool _isExecuted = false;  ///< Flag indicating whether the multiplication
                               ///< has been executed.
};