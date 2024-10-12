/**
 * @file TDifferentiator.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TDifferentiator class and associated
 * types for performing signal differentiation.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TDifferentiator.hpp"

#include <cmath>
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TDifferentiator::TDifferentiator(const TSignalLine* signalLine,
                                 const bool         performNormalization,
                                 const DifferentiationMethod method,
                                 std::optional<std::string>  xLabel,
                                 std::optional<std::string>  yLabel,
                                 std::optional<std::string>  graphLabel)
    : _params{.signalLine           = signalLine,
              .performNormalization = performNormalization,
              .method               = method,
              .xLabel               = std::move(xLabel),
              .yLabel               = std::move(yLabel),
              .graphLabel           = std::move(graphLabel)} {}

TDifferentiator::TDifferentiator(TDifferentiatorParams params)
    : _params(std::move(params)) {}

TDifferentiator::TDifferentiator(const TDifferentiator& differentiator)
    : _sl(differentiator._sl
              ? std::make_unique<TSignalLine>(*differentiator._sl)
              : nullptr),
      _params(differentiator._params),
      _isExecuted(differentiator._isExecuted) {}

TDifferentiator& TDifferentiator::operator=(
    const TDifferentiator& differentiator) {
    if (this == &differentiator) {
        return *this;
    }
    _sl         = differentiator._sl
                      ? std::make_unique<TSignalLine>(*differentiator._sl)
                      : nullptr;
    _params     = differentiator._params;
    _isExecuted = differentiator._isExecuted;
    return *this;
}

const TSignalLine* TDifferentiator::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Differentiator not executed");
    }
    return _sl.get();
}

const TDifferentiatorParams& TDifferentiator::getParams() const {
    return _params;
}

bool TDifferentiator::isExecuted() const {
    return _isExecuted;
}

void TDifferentiator::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TSignalCorrelator object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Invalid signal line (nullptr)");
    }
    if (_params.signalLine->getParams().pointsCount < 2) {
        throw SignalProcessingError("Insufficient number of points");
    }

    const double normalizeFactor =
        _params.performNormalization
            ? _params.signalLine->getParams().normalizeFactor.value()
            : 1.0;
    const std::size_t pointsCount = _params.signalLine->getParams().pointsCount;

    // Making new signal line for differentiation results
    TSignalLineParams slParams = _params.signalLine->getParams();
    slParams.xLabel            = _params.xLabel;
    slParams.yLabel            = _params.yLabel;
    slParams.graphLabel        = _params.graphLabel;
    switch (_params.method) {
        case DifferentiationMethod::CentralAndEdges:
            slParams.pointsCount = pointsCount;
            break;
        case DifferentiationMethod::CentralOnly:
            slParams.pointsCount = pointsCount - 2;
            break;
        default:
            throw SignalProcessingError("Invalid differentiation method");
    }
    _sl = std::make_unique<TSignalLine>(slParams,
                                        SL::Preference::PreferPointsCount);

    Point  point1;
    Point  point2;
    double deltaX = NAN;
    double deltaY = NAN;

    // Differentiation
    switch (_params.method) {
        case DifferentiationMethod::CentralAndEdges:
            point1 = _params.signalLine->getPoint(0);
            point2 = _params.signalLine->getPoint(1);
            deltaX = point2.x - point1.x;
            deltaY = point2.y - point1.y;
            _sl->setPoint(0, point1.x, deltaY / deltaX / normalizeFactor);

            point1 = _params.signalLine->getPoint(pointsCount - 2);
            point2 = _params.signalLine->getPoint(pointsCount - 1);
            deltaX = point2.x - point1.x;
            deltaY = point2.y - point1.y;
            _sl->setPoint(pointsCount - 1, point1.x,
                          deltaY / deltaX / normalizeFactor);

            for (std::size_t i = 1; i < pointsCount - 1; ++i) {
                point1 = _params.signalLine->getPoint(i - 1);
                point2 = _params.signalLine->getPoint(i + 1);
                deltaX = point2.x - point1.x;
                deltaY = point2.y - point1.y;
                _sl->setPoint(i, point1.x, deltaY / deltaX / normalizeFactor);
            }

            break;
        case DifferentiationMethod::CentralOnly:
            for (std::size_t i = 1; i < pointsCount - 1; ++i) {
                point1 = _params.signalLine->getPoint(i - 1);
                point2 = _params.signalLine->getPoint(i + 1);
                deltaX = point2.x - point1.x;
                deltaY = point2.y - point1.y;
                _sl->setPoint(i - 1, point1.x,
                              deltaY / deltaX / normalizeFactor);
            }
            break;
        default:
            throw SignalProcessingError("Invalid differentiation method");
    }

    _isExecuted = true;
}