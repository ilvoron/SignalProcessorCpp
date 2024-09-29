#include "TNoiseGenerator.h"
#include "TCore.h"
#include "TSignalLine.h"

#include <cstddef>
#include <memory>
#include <random>
#include <string>
#include <utility>

/**
 ** PUBLIC METHODS
 */

TNoiseGenerator::TNoiseGenerator(const TSignalLine* signalLine,
                                 double noiseAmplitude,
                                 NoiseType noiseType,
                                 std::string graphLabel)
    : _sl(std::make_unique<TSignalLine>(signalLine->getParams().pointsCount)),
      _params{signalLine, noiseAmplitude, noiseType, std::move(graphLabel)} {}

TNoiseGenerator::TNoiseGenerator(TNoiseGeneratorParams params)
    : _sl(std::make_unique<TSignalLine>(
          params.signalLine->getParams().pointsCount)),
      _params{std::move(params)} {}

const TSignalLine* TNoiseGenerator::getSignalLine() const {
  return _sl.get();
}

const TNoiseGeneratorParams& TNoiseGenerator::getParams() const {
  return _params;
}

void TNoiseGenerator::execute() {
  if (_sl == nullptr) {
    throw SignalProcesserException("Signal line is not initialized.");
  }

  const size_t pointsCount = _sl->getParams().pointsCount;
  const double noiseAmplitude = _params.noiseAmplitude;

  switch (_params.noiseType) {
    case NoiseType::White: {
      std::random_device randomDevice;
      std::mt19937 gen(randomDevice());
      std::uniform_real_distribution<> dist(-noiseAmplitude, noiseAmplitude);
      for (size_t i = 0; i < pointsCount; ++i) {
        const Point& originalPoint = _params.signalLine->getPoint(i);
        const double noise = dist(gen);
        _sl->setPoint(i, originalPoint.x, originalPoint.y + noise);
      }
      break;
    }

    default:
      throw SignalProcesserException("Unknown noise type.");
  }
}