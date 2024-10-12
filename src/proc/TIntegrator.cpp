/**
 * @file TIntegrator.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TIntegrator class and for
 * performing numerical integration on a signal line.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TIntegrator.hpp"
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstddef>

/*
 * PUBLIC METHODS
 */

TIntegrator::TIntegrator(const TSignalLine*           signalLine,
                         const INT::IntegrationMethod method)
    : _params{.signalLine = signalLine, .method = method} {}

TIntegrator::TIntegrator(const TIntegratorParams params) : _params(params) {}

double TIntegrator::getIntegral() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Integrator not executed");
    }
    return _integral;
}

const TIntegratorParams& TIntegrator::getParams() const {
    return _params;
}

bool TIntegrator::isExecuted() const {
    return _isExecuted;
}

void TIntegrator::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TIntegrator object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Invalid signal line (nullptr)");
    }
    if (_params.signalLine->getParams().pointsCount < 2) {
        throw SignalProcessingError(
            "Insufficient number of points: at least 2 points are required");
    }

    const std::size_t pointsCount = _params.signalLine->getParams().pointsCount;
    _integral                     = 0.0;

    switch (_params.method) {
        // Trapezoidal method: approximates the integral by calculating the area
        // of trapezoids between each pair of consecutive points
        case INT::IntegrationMethod::Trapezoidal:
            for (size_t i = 1; i < pointsCount; ++i) {
                const double xCoordBefore =
                    _params.signalLine->getPoint(i - 1).x;
                const double xCoord = _params.signalLine->getPoint(i).x;
                const double yCoordBefore =
                    _params.signalLine->getPoint(i - 1).y;
                const double yCoord = _params.signalLine->getPoint(i).y;
                _integral +=
                    (yCoordBefore + yCoord) / 2.0 * (xCoord - xCoordBefore);
            }
            break;

        // Simpson's method: approximates the integral using parabolic segments
        // Requires an odd number of points
        case INT::IntegrationMethod::Simpson:
            if (pointsCount % 2 == 0) {
                throw SignalProcessingError(
                    "Simpson's rule requires an odd number of points");
            }
            for (size_t i = 1; i < pointsCount - 1; i += 2) {
                const double xCoordBefore =
                    _params.signalLine->getPoint(i - 1).x;
                const double xCoordNext = _params.signalLine->getPoint(i + 1).x;
                const double yCoordBefore =
                    _params.signalLine->getPoint(i - 1).y;
                const double yCoord     = _params.signalLine->getPoint(i).y;
                const double yCoordNext = _params.signalLine->getPoint(i + 1).y;
                _integral += (xCoordNext - xCoordBefore) / 6.0 *
                             (yCoordBefore + 4 * yCoord + yCoordNext);
            }
            break;

        // Boole's method: uses a polynomial of degree 4 to approximate the
        // integral Requires that the number of points is of the form 4k + 1
        case INT::IntegrationMethod::Boole:
            if (pointsCount % 4 != 1) {
                throw SignalProcessingError(
                    "Boole's rule requires number of points to be 4k + 1");
            }
            for (size_t i = 0; i < pointsCount - 4; i += 4) {
                const double xCoord = _params.signalLine->getPoint(i).x;
                const double xCoordNext4 =
                    _params.signalLine->getPoint(i + 4).x;
                const double yCoord = _params.signalLine->getPoint(i).y;
                const double yCoordNext1 =
                    _params.signalLine->getPoint(i + 1).y;
                const double yCoordNext2 =
                    _params.signalLine->getPoint(i + 2).y;
                const double yCoordNext3 =
                    _params.signalLine->getPoint(i + 3).y;
                const double yCoordNext4 =
                    _params.signalLine->getPoint(i + 4).y;
                _integral += (xCoordNext4 - xCoord) / 90.0 *
                             (7 * yCoord + 32 * yCoordNext1 + 12 * yCoordNext2 +
                              32 * yCoordNext3 + 7 * yCoordNext4);
            }
            break;

        default:
            throw SignalProcessingError("Unknown integration method");
    }

    _isExecuted = true;
}