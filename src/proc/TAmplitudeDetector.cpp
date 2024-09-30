#include "TAmplitudeDetector.h"
#include "TCore.h"
#include "TIntegrator.h"
#include "TMultiplier.h"
#include "TSignalLine.h"

#include <cmath>
#include <memory>

/*
 * PUBLIC METHODS
 */

TAmplitudeDetector::TAmplitudeDetector(const TSignalLine* signalLine)
    : _params{signalLine} {}

TAmplitudeDetector::TAmplitudeDetector(TAmplitudeDetectorParams params)
    : _params(params) {}

double TAmplitudeDetector::getAmplitude() const {
  if (!_isExecuted) {
    throw SignalProcesserException("Amplitude detector not executed");
  }
  return _amplitude;
}

const TAmplitudeDetectorParams& TAmplitudeDetector::getParams() const {
  return _params;
}

bool TAmplitudeDetector::isExecuted() const {
  return _isExecuted;
}

void TAmplitudeDetector::execute(double normalizationInaccuracy) {
  if (_params.signalLine == nullptr) {
    throw SignalProcesserException("Invalid signal line (nullptr)");
  }
  if (!_params.signalLine->getParams().hasTime) {
    throw SignalProcesserException(
        "Signal line does not have time information");
  }

  const double maxValue = _params.signalLine->findMax();
  const double minValue = _params.signalLine->findMin();
  const double lowerBound = std::abs(maxValue) - normalizationInaccuracy;
  const double upperBound = std::abs(maxValue) + normalizationInaccuracy;
  if (std::abs(minValue) < lowerBound || std::abs(minValue) > upperBound) {
    _normalizedSignalLine = std::make_unique<TSignalLine>(
        _params.signalLine, 0.0, -(maxValue + minValue) / 2);
    _params.signalLine = _normalizedSignalLine.get();
  }

  TMultiplier powerSignalLine(_params.signalLine, _params.signalLine);
  powerSignalLine.execute();
  TIntegrator energy(powerSignalLine.getSignalLine());
  energy.execute();
  const double power =
      energy.getIntegral() / _params.signalLine->getParams().time;
  const double voltage = sqrt(power);
  _amplitude = sqrt(2) * voltage;

  _isExecuted = true;
}