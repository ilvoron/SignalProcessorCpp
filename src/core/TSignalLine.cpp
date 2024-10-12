/**
 * @file TSignalLine.cpp
 * @brief Implements the TSignalLine class methods, enabling manipulation and
 * analysis of discrete signal lines in a two-dimensional space.
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TSignalLine.hpp"
#include "TCore.hpp"

#include <cmath>
#include <cstddef>
#include <functional>
#include <optional>
#include <string>
#include <utility>

/************************
 **   PUBLIC METHODS   **
 ************************/

TSignalLine::TSignalLine(double                     samplingFrequency,
                         double                     duration,
                         std::optional<double>      oscillationFrequency,
                         std::optional<double>      initPhase,
                         std::optional<double>      offsetY,
                         std::optional<double>      amplitude,
                         std::optional<double>      normalizeFactor,
                         std::optional<std::string> xLabel,
                         std::optional<std::string> yLabel,
                         std::optional<std::string> graphLabel) {
    if (duration <= 0) {
        throw SignalProcessingError("Duration should be positive");
    }
    if (samplingFrequency <= 0) {
        throw SignalProcessingError("Sampling frequency should be positive");
    }

    _params.samplingFrequency    = samplingFrequency;
    _params.duration             = duration;
    _params.oscillationFrequency = oscillationFrequency;
    _params.initPhase            = initPhase;
    _params.offsetY              = offsetY;
    _params.amplitude            = amplitude;
    _params.normalizeFactor      = normalizeFactor;
    _params.xLabel               = std::move(xLabel);
    _params.yLabel               = std::move(yLabel);
    _params.graphLabel           = std::move(graphLabel);

    // Using ceil(duration * samplingFreq + 1) to ensure that we have enough
    // points to represent the signal for the specified duration, adding 1 for
    // rounding precision.
    _params.pointsCount =
        static_cast<std::size_t>(ceil(duration * samplingFrequency + 1));
    _points.resize(_params.pointsCount, Point{.x = 0.0, .y = 0.0});
}

TSignalLine::TSignalLine(std::size_t                pointsCount,
                         std::optional<std::string> xLabel,
                         std::optional<std::string> yLabel,
                         std::optional<std::string> graphLabel) {
    _params.xLabel      = std::move(xLabel);
    _params.yLabel      = std::move(yLabel);
    _params.graphLabel  = std::move(graphLabel);
    _params.pointsCount = pointsCount;
    _points.resize(pointsCount, Point{.x = 0.0, .y = 0.0});
}

TSignalLine::TSignalLine(TSignalLineParams                   params,
                         const std::optional<SL::Preference> preference) {
    switch (preference.value_or(SL::Preference::Auto)) {
        case SL::Preference::Auto:
        case SL::Preference::PreferDurationAndSamplingFreq:
            if (*params.duration <= 0) {
                throw SignalProcessingError("Duration should be positive");
            }
            if (*params.samplingFrequency <= 0) {
                throw SignalProcessingError(
                    "Sampling frequency should be positive");
            }

            // Using ceil(duration * samplingFreq + 1) to ensure that we have
            // enough points to represent the signal for the specified duration,
            // adding 1 for rounding precision.
            params.pointsCount = static_cast<std::size_t>(
                ceil(*params.duration * *params.samplingFrequency + 1));
            break;
        case SL::Preference::PreferPointsCount:
            break;
        default:
            throw SignalProcessingError("Invalid preference");
    }

    _points.resize(params.pointsCount, Point{.x = 0.0, .y = 0.0});
    _params = std::move(params);
}

TSignalLine::TSignalLine(const TSignalLine* signalLine,
                         const double       offsetX,
                         const double       offsetY) {
    if (signalLine == nullptr) {
        throw SignalProcessingError("Signal line pointer is null");
    }

    _params         = signalLine->getParams();
    _params.offsetY = std::nullopt;
    _points.resize(_params.pointsCount);

    // Using [] for performance: We use the operator[] to access points instead
    // of at(), as we are confident that points have been resized correctly, and
    // using at() would add unnecessary bounds checking.
    for (std::size_t i = 0; i < _params.pointsCount; ++i) {
        _points[i].x = signalLine->getPoint(i).x + offsetX;
        _points[i].y = signalLine->getPoint(i).y + offsetY;
    }
}

void TSignalLine::setPoint(const std::size_t index,
                           const double      xCoord,
                           const double      yCoord) {
    _points.at(index).x = xCoord;
    _points.at(index).y = yCoord;
}

void TSignalLine::setPoint(const std::size_t index, const Point point) {
    _points.at(index) = point;
}

const Point& TSignalLine::getPoint(const std::size_t index) const {
    return _points.at(index);
}

const TSignalLineParams& TSignalLine::getParams() const {
    return _params;
}

bool TSignalLine::equals(const TSignalLine*          signalLine,
                         const std::optional<double> inaccuracy) const {
    if (signalLine == nullptr) {
        throw SignalProcessingError("TSignalLine pointer is null");
    }

    const auto& paramsToCompare = signalLine->getParams();
    const auto  pointsCount     = _params.pointsCount;
    if (pointsCount != paramsToCompare.pointsCount) {
        return false;
    }

    // Perform the comparison of the first and last points within the
    // allowed inaccuracy. This serves as an approximation to determine if
    // the overall signals are similar, which is faster than comparing all
    // points.
    if (areCloseX(_points.at(0), signalLine->getPoint(0), inaccuracy) &&
        areCloseX(_points.at(pointsCount - 1),
                  signalLine->getPoint(pointsCount - 1), inaccuracy)) {
        return true;
    }

    return false;
}

double TSignalLine::findMax(const bool forceUpdate) const {
    return findByComparison(_params.maxValue, std::greater(), forceUpdate);
}

double TSignalLine::findMin(const bool forceUpdate) const {
    return findByComparison(_params.minValue, std::less(), forceUpdate);
}

void TSignalLine::removeDCComponent(std::optional<double> inaccuracy) {
    const double maxValue   = findMax();
    const double minValue   = findMin();
    const double lowerBound = std::abs(maxValue) - *inaccuracy;
    const double upperBound = std::abs(maxValue) + *inaccuracy;
    if (std::abs(minValue) < lowerBound || std::abs(minValue) > upperBound) {
        for (size_t i = 0; i < _params.pointsCount; ++i) {
            const auto& [x, y] = getPoint(i);
            setPoint(i, x, y - (maxValue + minValue) / 2);
        }
    }
}

/* PRIVATE METHODS */

double TSignalLine::findByComparison(
    std::optional<double>&                     cachedValue,
    const std::function<bool(double, double)>& comparator,
    const bool                                 forceUpdate) const {
    if (cachedValue && !forceUpdate) {
        return *cachedValue;
    }

    auto value = _points[0].y;
    for (const auto& [x, y] : _points) {
        if (comparator(y, value)) {
            value = y;
        }
    }

    cachedValue = value;
    return value;
}

/************************
 **   STATIC METHODS   **
 ************************/

bool TSignalLine::areCloseX(const Point&          point1,
                            const Point&          point2,
                            std::optional<double> inaccuracy) {
    if (inaccuracy) {
        if (*inaccuracy < 0) {
            throw SignalProcessingError("Inaccuracy should be positive");
        }
        return std::abs(point1.x - point2.x) <= *inaccuracy;
    }
    return point1.x == point2.x;
}

bool TSignalLine::areCloseY(const Point&          point1,
                            const Point&          point2,
                            std::optional<double> inaccuracy) {
    if (inaccuracy) {
        if (*inaccuracy < 0) {
            throw SignalProcessingError("Inaccuracy should be positive");
        }
        return std::abs(point1.y - point2.y) <= *inaccuracy;
    }
    return point1.y == point2.y;
}

bool TSignalLine::areClose(const Point&                point1,
                           const Point&                point2,
                           const std::optional<double> inaccuracy) {
    return areCloseX(point1, point2, inaccuracy) &&
           areCloseY(point1, point2, inaccuracy);
}