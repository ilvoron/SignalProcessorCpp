#include "TSignalLine.h"
#include "TCore.h"

#include <cmath>
#include <cstddef>
#include <string>
#include <utility>

/*
 * PRIVATE METHODS
 */

void TSignalLine::validatePointsInitialization() const {
  if (_points.empty()) {
    throw SignalProcesserException("Points not initialized");
  }
}

/*
 * PUBLIC METHODS
 */

TSignalLine::TSignalLine(double time,
                         double oscillationFreq,
                         double initPhase,
                         double offsetY,
                         double amplitude,
                         double samplingFreq,
                         double normalizeFactor,
                         std::string xLabel,
                         std::string yLabel,
                         std::string graphLabel)
    : _params{static_cast<std::size_t>(ceil(time * samplingFreq + 1)),
              time,
              oscillationFreq,
              initPhase,
              offsetY,
              amplitude,
              samplingFreq,
              normalizeFactor,
              0.0,
              0.0,
              true,
              true,
              true,
              true,
              true,
              true,
              true,
              true,
              false,
              false,
              std::move(xLabel),
              std::move(yLabel),
              std::move(graphLabel)} {
  if (time <= 0) {
    throw SignalProcesserException("Time should be positive");
  }
  if (samplingFreq <= 0) {
    throw SignalProcesserException("Sampling frequency should be positive");
  }
  _points.resize(_params.pointsCount, Point{0.0, 0.0});
}

TSignalLine::TSignalLine(std::size_t pointsCount,
                         std::string xLabel,
                         std::string yLabel,
                         std::string graphLabel) {
  _params = {pointsCount,
             0.0,
             0.0,
             0.0,
             0.0,
             0.0,
             0.0,
             0.0,
             0.0,
             0.0,
             true,
             false,
             false,
             false,
             false,
             false,
             false,
             false,
             false,
             false,
             std::move(xLabel),
             std::move(yLabel),
             std::move(graphLabel)};
  _points.resize(pointsCount, Point{0.0, 0.0});
}

TSignalLine::TSignalLine(TSignalLineParams params)
    : _params(std::move(params)) {
  if (!canFormFromTimeOrFrequency() && !_params.hasPointsCount) {
    throw SignalProcesserException("Invalid parameters");
  }
  if (canFormFromTimeOrFrequency()) {
    _params.pointsCount =
        static_cast<std::size_t>(ceil(_params.time * _params.samplingFreq + 1));
    _params.hasPointsCount = true;
  }
  _points.resize(_params.pointsCount, Point{0.0, 0.0});
}

TSignalLine::TSignalLine(const TSignalLine* signalLine,
                         double offsetX,
                         double offsetY) {
  if (signalLine == nullptr) {
    throw SignalProcesserException("Signal line pointer is null");
  }

  _params = signalLine->getParams();
  _points.resize(_params.pointsCount, Point{0.0, 0.0});
  for (std::size_t i = 0; i < _params.pointsCount; i++) {
    _points.at(i).x = signalLine->getPoint(i).x + offsetX;
    _points.at(i).y = signalLine->getPoint(i).y + offsetY;
  }
}

void TSignalLine::setPoint(std::size_t index, double xCoord, double yCoord) {
  validatePointsInitialization();
  _points.at(index).x = xCoord;
  _points.at(index).y = yCoord;
}

const Point& TSignalLine::getPoint(std::size_t index) const {
  validatePointsInitialization();
  return _points.at(index);
}

const TSignalLineParams& TSignalLine::getParams() const {
  return _params;
}

bool TSignalLine::equals(const TSignalLine* signalLine,
                         double inaccuracy) const {
  validatePointsInitialization();
  if (signalLine == nullptr) {
    throw SignalProcesserException("TSignalLine pointer is null");
  }
  signalLine->validatePointsInitialization();
  if (inaccuracy < 0) {
    throw SignalProcesserException("Inaccuracy should be positive");
  }

  const TSignalLineParams paramsToCompare = signalLine->getParams();
  if (_params.pointsCount != paramsToCompare.pointsCount) {
    return false;
  }

  if (areCloseX(_points.at(0), signalLine->getPoint(0), inaccuracy) &&
      areCloseX(_points.at(_params.pointsCount - 1),
                signalLine->getPoint(_params.pointsCount - 1), inaccuracy)) {
    return true;
  }

  return false;
}

bool TSignalLine::canFormFromTimeOrFrequency() const {
  return _params.hasTime || _params.hasOscillationFreq;
}

double TSignalLine::findMax(bool forceUpdate) const {
  if (_params.hasMaxValue && !forceUpdate) {
    return _params.maxValue;
  }

  double max = _points.at(0).y;
  for (const Point& point : _points) {
    if (point.y > max) {
      max = point.y;
    }
  }

  _params.maxValue = max;
  _params.hasMaxValue = true;
  return max;
}

double TSignalLine::findMin(bool forceUpdate) const {
  if (_params.hasMinValue && !forceUpdate) {
    return _params.minValue;
  }

  double min = _points.at(0).y;
  for (const Point& point : _points) {
    if (point.y < min) {
      min = point.y;
    }
  }

  _params.minValue = min;
  _params.hasMinValue = true;
  return min;
}

bool TSignalLine::areCloseX(const Point& point1,
                            const Point& point2,
                            double inaccuracy) {
  const double leftBound = point1.x - inaccuracy;
  const double rightBound = point1.x + inaccuracy;
  return point2.x >= leftBound && point2.x <= rightBound;
}

bool TSignalLine::areCloseY(const Point& point1,
                            const Point& point2,
                            double inaccuracy) {
  const double lowerBound = point1.y - inaccuracy;
  const double upperBound = point1.y + inaccuracy;
  return point2.y >= lowerBound && point2.y <= upperBound;
}

bool TSignalLine::areClose(const Point& point1,
                           const Point& point2,
                           double inaccuracy) {
  return areCloseX(point1, point2, inaccuracy) &&
         areCloseY(point1, point2, inaccuracy);
}