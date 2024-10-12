/**
 * @file TSummator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TSummator class and its associated
 * parameters for summing two signal lines.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo Sum of two different signals: end summing if one of the signals ends OR
 * add zeros to the end of the shorter signal
 */

#pragma once

#include "TSignalLine.hpp"

#include <memory>
#include <optional>
#include <string>

/**
 * @namespace SUMM
 * @brief Contains default parameters used in signal summation.
 */
namespace SUMM {

    // Graphical parameters
    static const std::string DEFAULT_GRAPH_LABEL =
        "Summation";  ///< Default graph label.

}  // namespace SUMM

/**
 * @struct TSummatorParams
 * @brief Parameters for summing two signal lines.
 */
struct TSummatorParams {
    // Signal parameters
    const TSignalLine* signalLine1 =
        nullptr;  ///< Pointer to the first signal line.
    const TSignalLine* signalLine2 =
        nullptr;  ///< Pointer to the second signal line.

    // Summation parameters
    std::optional<double> inaccuracy =
        SL::DEFAULT_INACCURACY;  ///< Allowed inaccuracy for
                                 ///< summing the signals

    // Graphical parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        SUMM::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TSummator
 * @brief Class for summing two signal lines into one by summing their values on
 * a point-by-point basis.
 */
class TSummator {
   public:
    /**
     * @brief Constructs a TSummator with two signal lines and summation
     * parameters.
     *
     * @param signalLine1 Pointer to the first signal line.
     * @param signalLine2 Pointer to the second signal line.
     * @param inaccuracy Allowed inaccuracy for summing the signals.
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     */
    explicit TSummator(
        const TSignalLine*         signalLine1,
        const TSignalLine*         signalLine2,
        std::optional<double>      inaccuracy = SL::DEFAULT_INACCURACY,
        std::optional<std::string> xLabel     = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel     = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = SUMM::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TSummator object using TSummatorParams.
     *
     * @param params A structure containing the parameters for signal summation.
     */
    explicit TSummator(TSummatorParams params);

    /**
     * @brief Default destructor.
     */
    ~TSummator() = default;

    /**
     * @brief Copy constructor.
     */
    TSummator(const TSummator& summator);

    /**
     * @brief Default move constructor.
     */
    TSummator(TSummator&&) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    TSummator& operator=(const TSummator& summator);

    /**
     * @brief Default move assignment operator.
     */
    TSummator& operator=(TSummator&&) noexcept = default;

    /**
     * @brief Retrieves the summed signal line.
     *
     * @return const TSignalLine* Pointer to the resulting summed signal line.
     *
     * @throw SignalProcessingError If the summation process has not been
     * executed.
     */
    [[nodiscard]] const TSignalLine* getSignalLine() const;

    /**
     * @brief Retrieves the parameters used for signal summation.
     *
     * @return const TSummatorParams& Reference to the summation parameters.
     */
    [[nodiscard]] const TSummatorParams& getParams() const;

    /**
     * @brief Checks whether the summation has been executed.
     *
     * @return bool True if the summation process has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the summation of the two signal lines.
     *
     * @throw SignalProcessingError If one of the signal lines is null or if the
     * signal lines aren't equal.
     */
    void execute();

   private:
    std::unique_ptr<TSignalLine> _sl =
        nullptr;                   ///< Pointer to the summed signal line.
    TSummatorParams _params = {};  ///< Parameters for signal summation.
    bool            _isExecuted =
        false;  ///< Flag indicating whether the summation has been executed.
};