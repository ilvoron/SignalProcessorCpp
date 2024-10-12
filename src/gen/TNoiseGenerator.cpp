/**
 * @file TNoiseGenerator.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TNoiseGenerator class for noise
 * generation on signal lines.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TNoiseGenerator.hpp"
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TNoiseGenerator::TNoiseGenerator(const TSignalLine*         signalLine,
                                 const double               noiseAmplitude,
                                 const NGEN::NoiseType      noiseType,
                                 std::optional<std::string> xLabel,
                                 std::optional<std::string> yLabel,
                                 std::optional<std::string> graphLabel)
    : _params{.signalLine     = signalLine,
              .noiseAmplitude = noiseAmplitude,
              .noiseType      = noiseType,
              .xLabel         = std::move(xLabel),
              .yLabel         = std::move(yLabel),
              .graphLabel     = std::move(graphLabel)} {}

TNoiseGenerator::TNoiseGenerator(TNoiseGeneratorParams params)
    : _params{std::move(params)} {}

TNoiseGenerator::TNoiseGenerator(const TNoiseGenerator& generator)
    : _sl(generator._sl ? std::make_unique<TSignalLine>(*generator._sl)
                        : nullptr),
      _params(generator._params),
      _isExecuted(generator._isExecuted) {}

TNoiseGenerator& TNoiseGenerator::operator=(const TNoiseGenerator& generator) {
    if (this == &generator) {
        return *this;
    }
    _sl =
        generator._sl ? std::make_unique<TSignalLine>(*generator._sl) : nullptr;
    _params     = generator._params;
    _isExecuted = generator._isExecuted;
    return *this;
}

const TSignalLine* TNoiseGenerator::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Noise Generator not executed");
    }
    return _sl.get();
}

const TNoiseGeneratorParams& TNoiseGenerator::getParams() const {
    return _params;
}

bool TNoiseGenerator::isExecuted() const {
    return _isExecuted;
}

void TNoiseGenerator::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TNoiseGenerator object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Signal line is not specified.");
    }

    TSignalLineParams slParams = _params.signalLine->getParams();
    slParams.xLabel            = _params.xLabel;
    slParams.yLabel            = _params.yLabel;
    slParams.graphLabel        = _params.graphLabel;
    _sl                        = std::make_unique<TSignalLine>(slParams);

    const size_t pointsCount    = _sl->getParams().pointsCount;
    const double noiseAmplitude = _params.noiseAmplitude;

    switch (_params.noiseType) {
        case NGEN::NoiseType::White: {
            // Initialize random number generator for white noise with uniform
            // distribution
            std::random_device             randomDevice;
            std::mt19937                   gen(randomDevice());
            std::uniform_real_distribution dist(-noiseAmplitude,
                                                noiseAmplitude);

            // Apply noise to each point in the signal line
            for (size_t i = 0; i < pointsCount; ++i) {
                const auto& [x, y] = _params.signalLine->getPoint(i);
                const double noise =
                    dist(gen);  // Generate random noise within the specified
                                // amplitude range
                _sl->setPoint(i, x, y + noise);
            }
            break;
        }

        default:
            throw SignalProcessingError("Unknown noise type.");
    }

    _isExecuted = true;
}