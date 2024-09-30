#define _USE_MATH_DEFINES

#include "TGenerator.h"
#include "TCore.h"
#include "TSignalLine.h"

#include <cmath>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;
#endif

const double TWO_PI = 2 * M_PI;

/*
 * PUBLIC METHODS
 */

TGenerator::TGenerator(double time,
                       double oscillationFreq,
                       double initPhase,
                       double offsetY,
                       double amplitude,
                       double samplingFreq,
                       std::string xLabel,
                       std::string yLabel,
                       std::string graphLabel)
    : _params{time,
              oscillationFreq,
              initPhase,
              offsetY,
              amplitude,
              samplingFreq,
              std::move(xLabel),
              std::move(yLabel),
              std::move(graphLabel)} {}

TGenerator::TGenerator(TGeneratorParams params) : _params(std::move(params)) {}

const TSignalLine* TGenerator::getSignalLine() const {
  if (!_isExecuted) {
    throw SignalProcesserException("Generator not executed");
  }
  return _sl.get();
}

const TGeneratorParams& TGenerator::getParams() const {
  return _params;
}

bool TGenerator::isExecuted() const {
  return _isExecuted;
}

void TGenerator::execute() {
  _sl = std::make_unique<TSignalLine>(
      _params.time, _params.oscillationFreq, _params.initPhase, _params.offsetY,
      _params.amplitude, _params.samplingFreq, TWO_PI, _params.xLabel,
      _params.yLabel, _params.graphLabel);

  const TSignalLineParams params = _sl->getParams();
  const double twoPiFreq =
      TWO_PI * params.oscillationFreq / params.samplingFreq;
  double xCoord = 0.0;
  double yCoord = 0.0;
  for (std::size_t i = 0; i < params.pointsCount; i++) {
    xCoord = static_cast<double>(i) / params.samplingFreq;
    yCoord = params.amplitude *
                 sin(twoPiFreq * static_cast<double>(i) + params.initPhase) +
             params.offsetY;
    _sl->setPoint(i, xCoord, yCoord);
  }
  _isExecuted = true;
}