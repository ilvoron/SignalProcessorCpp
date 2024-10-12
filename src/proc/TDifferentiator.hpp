/**
 * @file TDifferentiator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TDifferentiator class and associated
 * types for performing signal differentiation.
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
 * @enum DifferentiationMethod
 * @brief Specifies the method to be used for differentiation.
 *
 * @details This enumeration defines the two possible differentiation methods:
 *
 * - `CentralOnly`: This method applies only central differences for all points.
 *   It reduces the length of the differentiated signal by 2 points compared to
 * the original signal (1 point is removed from the beginning and 1 from the
 * end) since central differences require both a previous and a next point for
 * computation.
 *
 * - `CentralAndEdges`: This method applies central differences to the interior
 * points, but for the first and last points of the signal, it uses one-sided
 * differences (forward difference for the first point, backward difference for
 * the last point). This method maintains the same number of points in the
 * resulting signal as in the original signal, as it doesn't discard the edge
 * points.
 */
enum class DifferentiationMethod : std::uint8_t {
    CentralOnly,  ///< Use only central differences (signal length will be
    ///< reduced by 2 points).
    CentralAndEdges  ///< Use central differences and one-sided at the edges
    ///< (signal length will remain the same).
};

/**
 * @namespace DIFF
 * @brief Contains default parameters used in differentiation.
 */
namespace DIFF {
    // Graphical parameters
    static const std::string DEFAULT_GRAPH_LABEL =
        "Differentiation";  ///< Default graph label.

    // Differentiation parameters
    static constexpr bool DEFAULT_PERFORM_NORMALIZATION =
        true;  ///< Default normalization flag.
    static constexpr auto DEFAULT_DIFF_METHOD =
        DifferentiationMethod::CentralAndEdges;  ///< Default differentiation
                                                 ///< method.
}  // namespace DIFF

/**
 * @struct TDifferentiatorParams
 * @brief Parameters for differentiating a signal line.
 */
struct TDifferentiatorParams {
    // Signal parameters
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to differentiate.

    // Differentiation parameters
    bool performNormalization =
        DIFF::DEFAULT_PERFORM_NORMALIZATION;  ///< Flag to perform
                                              ///< normalization.
    DifferentiationMethod method =
        DIFF::DEFAULT_DIFF_METHOD;  ///< Method for
                                    ///< differentiation.

    // Graphical parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        DIFF::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.
};

/**
 * @class TDifferentiator
 * @brief Class for differentiating a signal line.
 */
class TDifferentiator {
   public:
    /**
     * @brief Constructs a TDifferentiator with a signal line and
     * differentiation parameters.
     *
     * @param signalLine Pointer to the signal line to differentiate.
     * @param performNormalization Flag to perform normalization.
     * @param method Method for differentiation
     * @param xLabel Label for the x-axis.
     * @param yLabel Label for the y-axis.
     * @param graphLabel Label for the graph.
     */
    explicit TDifferentiator(
        const TSignalLine* signalLine,
        bool performNormalization         = DIFF::DEFAULT_PERFORM_NORMALIZATION,
        DifferentiationMethod      method = DIFF::DEFAULT_DIFF_METHOD,
        std::optional<std::string> xLabel = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = DIFF::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a TDifferentiator with differentiation parameters.
     *
     * @param params A structure containing the parameters for signal
     * differentiation.
     */
    explicit TDifferentiator(TDifferentiatorParams params);

    /**
     * @brief Default destructor.
     */
    ~TDifferentiator() = default;

    /**
     * @brief Copy constructor.
     */
    TDifferentiator(const TDifferentiator& differentiator);

    /**
     * @brief Default move constructor.
     */
    TDifferentiator(TDifferentiator&&) noexcept = default;

    /**
     * @brief Copy assignment operator.
     */
    TDifferentiator& operator=(const TDifferentiator& differentiator);

    /**
     * @brief Default move assignment operator.
     */
    TDifferentiator& operator=(TDifferentiator&&) noexcept = default;

    /**
     * @brief Retrieves the differentiated signal line.
     *
     * @return const TSignalLine* Pointer to the resulting differentiated signal
     * line.
     *
     * @throw SignalProcessingError if the differentiation process has not been
     * executed.
     */
    [[nodiscard]] const TSignalLine* getSignalLine() const;

    /**
     * @brief Retrieves the parameters used for signal differentiation.
     *
     * @return const TDifferentiatorParams& Reference to the differentiation
     * parameters.
     */
    [[nodiscard]] const TDifferentiatorParams& getParams() const;

    /**
     * @brief Checks whether the differentiation has been executed.
     *
     * @return bool True if the differentiation process has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the differentiation of the signal line.
     *
     * @throw SignalProcessingError if the signal line is invalid or has an
     * insufficient number of points.
     */
    void execute();

   private:
    std::unique_ptr<TSignalLine>
                          _sl;  ///< Pointer to the differentiated signal line.
    TDifferentiatorParams _params;  ///< Parameters for signal differentiation.
    bool                  _isExecuted =
        false;  ///< Indicates if the differentiation has been executed.
};