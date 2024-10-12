/**
 * @file TGenerator.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TGenerator class for signal
 * waveform generation.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TGenerator.hpp"
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <utility>

/************************
 **   PUBLIC METHODS   **
 ************************/

TGenerator::TGenerator(const double                samplingFrequency,
                       const double                duration,
                       const double                oscillationFrequency,
                       const double                initPhase,
                       const double                offsetY,
                       const double                amplitude,
                       const GEN::GenerationMethod method,
                       const std::optional<double> clampValue,
                       std::optional<std::string>  xLabel,
                       std::optional<std::string>  yLabel,
                       std::optional<std::string>  graphLabel)
    : _params{.samplingFreq    = samplingFrequency,
              .duration = duration,
              .oscillationFreq = oscillationFrequency,
              .initPhase       = initPhase,
              .offsetY         = offsetY,
              .amplitude       = amplitude,
              .method          = method,
              .clampValue      = clampValue,
              .xLabel          = std::move(xLabel),
              .yLabel          = std::move(yLabel),
              .graphLabel      = std::move(graphLabel)} {
    if (_params.method == GEN::GenerationMethod::TangentWave ||
        _params.method == GEN::GenerationMethod::CotangentWave) {
        if (!_params.clampValue) {
            throw SignalProcessingError("Clamp value should be specified");
        }
        if (*_params.clampValue < 0) {
            throw SignalProcessingError("Clamp value should be positive");
        }
    }

    TSignalLineParams slParams;
    slParams.samplingFrequency = _params.samplingFreq;
    slParams.duration     = _params.duration;
    slParams.oscillationFrequency         = _params.oscillationFreq;
    slParams.initPhase           = _params.initPhase;
    slParams.offsetY             = _params.offsetY;
    slParams.amplitude           = _params.amplitude;
    slParams.xLabel              = _params.xLabel;
    slParams.yLabel              = _params.yLabel;
    slParams.graphLabel          = _params.graphLabel;

    switch (_params.method) {
        case GEN::GenerationMethod::SineWave:
        case GEN::GenerationMethod::CosineWave:
        case GEN::GenerationMethod::TangentWave:
        case GEN::GenerationMethod::CotangentWave:
            slParams.normalizeFactor = GEN::DEFAULT_NORMALIZE_FACTOR_SIN;
            break;
    }

    // TSignalLine constructor has a check of input parameters, so we can safely
    // use them
    _sl = std::make_unique<TSignalLine>(slParams);
}

TGenerator::TGenerator(TGeneratorParams params) : _params(std::move(params)) {
    if (_params.method == GEN::GenerationMethod::TangentWave ||
        _params.method == GEN::GenerationMethod::CotangentWave) {
        if (!_params.clampValue) {
            throw SignalProcessingError("Clamp value should be specified");
        }
        if (*_params.clampValue < 0) {
            throw SignalProcessingError("Clamp value should be positive");
        }
    }

    TSignalLineParams slParams;
    slParams.samplingFrequency = _params.samplingFreq;
    slParams.duration     = _params.duration;
    slParams.oscillationFrequency         = _params.oscillationFreq;
    slParams.initPhase           = _params.initPhase;
    slParams.offsetY             = _params.offsetY;
    slParams.amplitude           = _params.amplitude;
    slParams.xLabel              = _params.xLabel;
    slParams.yLabel              = _params.yLabel;
    slParams.graphLabel          = _params.graphLabel;

    switch (_params.method) {
        case GEN::GenerationMethod::SineWave:
        case GEN::GenerationMethod::CosineWave:
        case GEN::GenerationMethod::TangentWave:
        case GEN::GenerationMethod::CotangentWave:
            slParams.normalizeFactor = GEN::DEFAULT_NORMALIZE_FACTOR_SIN;
            break;
    }

    // TSignalLine constructor has a check of input parameters, so we can safely
    // use them
    _sl = std::make_unique<TSignalLine>(slParams);
}

TGenerator::TGenerator(const TGenerator& generator)
    : _sl(generator._sl ? std::make_unique<TSignalLine>(*generator._sl)
                        : nullptr),
      _params(generator._params),
      _isExecuted(generator._isExecuted) {}

TGenerator& TGenerator::operator=(const TGenerator& generator) {
    if (this == &generator) {
        return *this;
    }
    _sl =
        generator._sl ? std::make_unique<TSignalLine>(*generator._sl) : nullptr;
    _params     = generator._params;
    _isExecuted = generator._isExecuted;
    return *this;
}

const TSignalLine* TGenerator::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Generator not executed");
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
    const auto params = _sl->getParams();
    const auto twoPiFreq =
        TWO_PI * _params.oscillationFreq / _params.samplingFreq;

    switch (_params.method) {
        case GEN::GenerationMethod::SineWave:
            for (std::size_t i = 0; i < params.pointsCount; ++i) {
                const double xCoord =
                    static_cast<double>(i) / _params.samplingFreq;
                const double yCoord =
                    _params.amplitude * sin(twoPiFreq * static_cast<double>(i) +
                                            _params.initPhase) +
                    _params.offsetY;
                _sl->setPoint(i, xCoord, yCoord);
            }
            break;

        case GEN::GenerationMethod::CosineWave:
            for (std::size_t i = 0; i < params.pointsCount; ++i) {
                const double xCoord =
                    static_cast<double>(i) / _params.samplingFreq;
                const double yCoord =
                    _params.amplitude * cos(twoPiFreq * static_cast<double>(i) +
                                            _params.initPhase) +
                    _params.offsetY;
                _sl->setPoint(i, xCoord, yCoord);
            }
            break;

        case GEN::GenerationMethod::TangentWave:
            for (std::size_t i = 0; i < params.pointsCount; ++i) {
                const double xCoord =
                    static_cast<double>(i) / _params.samplingFreq;
                double yCoord =
                    _params.amplitude *
                    tan(twoPiFreq * static_cast<double>(i) + _params.initPhase);

                // Clamp yCoord to prevent extreme values from disrupting the
                // graph
                if (yCoord > *_params.clampValue) {
                    yCoord = *_params.clampValue;
                } else if (yCoord < -*_params.clampValue) {
                    yCoord = -*_params.clampValue;
                }

                // Adjust the final y-coordinate by adding the vertical offset
                yCoord += _params.offsetY;
                _sl->setPoint(i, xCoord, yCoord);
            }
            break;

        case GEN::GenerationMethod::CotangentWave:
            for (std::size_t i = 0; i < params.pointsCount; ++i) {
                const double xCoord =
                    static_cast<double>(i) / _params.samplingFreq;
                const double tanValue =
                    _params.amplitude *
                    tan(twoPiFreq * static_cast<double>(i) + _params.initPhase);

                double yCoord = 0.0;

                // Handle the asymptote by setting yCoord to the clamp value
                // when tanValue is near zero
                if (std::abs(tanValue) <
                    std::numeric_limits<double>::epsilon()) {
                    yCoord = *_params.clampValue * (tanValue > 0 ? 1 : -1);
                } else {
                    // Calculate the cotangent by taking the reciprocal of the
                    // tangent value
                    yCoord = _params.amplitude * (1.0 / tanValue);
                }

                // Clamp yCoord to prevent graph disruption from extreme values
                if (yCoord > *_params.clampValue) {
                    yCoord = *_params.clampValue;
                } else if (yCoord < -*_params.clampValue) {
                    yCoord = -*_params.clampValue;
                }

                // Adjust the final y-coordinate by adding the vertical offset
                yCoord += _params.offsetY;
                _sl->setPoint(i, xCoord, yCoord);
            }
            break;

        default:
            throw SignalProcessingError("Unknown generation method");
    }

    _isExecuted = true;
}