/**
 * @file TIntegrator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TIntegrator class and its associated
 * parameters for performing numerical integration on a signal line.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TSignalLine.hpp"

#include <cstdint>

/**
 * @namespace INT
 * @brief Contains default parameters used in numerical integration.
 */
namespace INT {

    /**
     * @enum IntegrationMethod
     * @brief Specifies the available methods for numerical integration.
     *
     * @details This enumeration defines several methods for performing
     * numerical integration:
     *
     * - `Trapezoidal`:
     *   This method uses the trapezoidal rule for numerical integration. It
     * approximates the area under the curve by dividing the curve into
     * trapezoids. This method requires at least two points for computation and
     * works well for functions that are linear or approximately linear between
     * points. The trapezoidal rule calculates the area of each trapezoid and
     * sums them up.
     *   - Minimum points required: 2.
     *
     * - `Simpson`:
     *   This method uses Simpson's rule, which is based on approximating the
     * function by a quadratic polynomial on each segment. It requires an odd
     * number of points (at least 3) because it calculates the area using pairs
     * of intervals, forming parabolic segments that give a higher level of
     * accuracy than the trapezoidal rule for smooth functions.
     *   - Minimum points required: 3 (must be an odd number).
     *
     * - `Boole`:
     *   This method uses Boole's rule (also known as the fifth-degree
     * polynomial rule), which is a higher-order numerical integration method.
     * It approximates the function using a polynomial of degree 5 on each
     * segment. Boole's rule requires that the number of points satisfies the
     * condition \(4k + 1\), meaning the number of points must be equal to 5, 9,
     * 13, etc.
     *   - Minimum points required: 5 (must satisfy \(4k + 1\) condition).
     */
    enum class IntegrationMethod : std::uint8_t {
        Trapezoidal,  ///< Trapezoidal rule (requires at least 2 points).
        Simpson,      ///< Simpson's rule (requires at least 3 points, and the
                      ///< number must be odd).
        Boole  ///< Boole's rule (requires at least 5 points, and the number
               ///< must satisfy 4k + 1).
    };

    static constexpr auto DEFAULT_INT_METHOD =
        IntegrationMethod::Trapezoidal;  ///< Default integration method.

}  // namespace INT

/**
 * @struct TIntegratorParams
 * @brief Defines the parameters used for numerical integration.
 */
struct TIntegratorParams {
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to be integrated.
    INT::IntegrationMethod method =
        INT::DEFAULT_INT_METHOD;  ///< Method for numerical integration.
};

/**
 * @class TIntegrator
 * @brief Class for performing numerical integration on a signal line.
 */
class TIntegrator {
   public:
    /**
     * @brief Constructs a TIntegrator with a signal line and an integration
     * method.
     *
     * @param signalLine Pointer to the signal line to integrate.
     * @param method The method to use for integration.
     */
    explicit TIntegrator(
        const TSignalLine*     signalLine,
        INT::IntegrationMethod method = INT::IntegrationMethod::Trapezoidal);

    /**
     * @brief Constructs a TIntegrator with integration parameters.
     *
     * @param params Structure containing the parameters for signal
     * integration.
     */
    explicit TIntegrator(TIntegratorParams params);

    /**
     * @brief Default destructor.
     */
    ~TIntegrator() = default;

    /**
     * @brief Default copy constructor.
     */
    TIntegrator(const TIntegrator&) = default;

    /**
     * @brief Default move constructor.
     */
    TIntegrator(TIntegrator&&) noexcept = default;

    /**
     * @brief Default copy assignment operator.
     */
    TIntegrator& operator=(const TIntegrator&) = default;

    /**
     * @brief Default move assignment operator.
     */
    TIntegrator& operator=(TIntegrator&&) noexcept = default;

    /**
     * @brief Retrieves the computed integral.
     *
     * @return double The result of the numerical integration.
     *
     * @throw SignalProcessingError If the integration process has not been
     * executed.
     */
    [[nodiscard]] double getIntegral() const;

    /**
     * @brief Retrieves the parameters used for integration.
     *
     * @return const TIntegratorParams& Reference to the integration
     * parameters.
     */
    [[nodiscard]] const TIntegratorParams& getParams() const;

    /**
     * @brief Checks whether the integration has been executed.
     *
     * @return bool True if the integration process has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the numerical integration of the signal line.
     *
     * @throw SignalProcessingError If the signal line is invalid or has an
     * insufficient number of points.
     */
    void execute();

   private:
    double            _integral = 0.0;  ///< Stores the computed integral value.
    TIntegratorParams _params   = {};   ///< Parameters for integration.
    bool              _isExecuted =
        false;  ///< Indicates if the integration has been executed.
};