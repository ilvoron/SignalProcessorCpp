/**
 * @file TFrequencyAnalyzer.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TFrequencyAnalyzer class used for
 * converting signals from the time domain to the frequency domain.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TFrequencyAnalyzer.hpp"
#include "TCore.hpp"
#include "TCorrelator.hpp"
#include "TGenerator.hpp"
#include "TSignalLine.hpp"

#include <cmath>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TFrequencyAnalyzer::TFrequencyAnalyzer(const TSignalLine*  signalLine,
                                       const double        fromFrequency,
                                       const double        toFrequency,
                                       const double        stepFrequency,
                                       const std::optional<bool> useAbsoluteValue,
                                       std::optional<std::string> xLabel,
                                       std::optional<std::string> yLabel,
                                       std::optional<std::string> graphLabel)
    : _params{.signalLine       = signalLine,
              .fromFrequency    = fromFrequency,
              .toFrequency      = toFrequency,
              .stepFrequency    = stepFrequency,
              .useAbsoluteValue = useAbsoluteValue,
              .xLabel           = std::move(xLabel),
              .yLabel           = std::move(yLabel),
              .graphLabel       = std::move(graphLabel)} {
    if (_params.fromFrequency >= _params.toFrequency) {
        throw SignalProcessingError("Invalid frequency range");
    }
}

TFrequencyAnalyzer::TFrequencyAnalyzer(TFrequencyAnalyzerParams params)
    : _params(std::move(params)) {
    if (_params.fromFrequency >= _params.toFrequency) {
        throw SignalProcessingError("Invalid frequency range");
    }
}

TFrequencyAnalyzer::TFrequencyAnalyzer(const TFrequencyAnalyzer& analyzer)
    : _sl(analyzer._sl ? std::make_unique<TSignalLine>(*analyzer._sl)
                       : nullptr),
      _params(analyzer._params),
      _isExecuted(analyzer._isExecuted) {}

TFrequencyAnalyzer& TFrequencyAnalyzer::operator=(
    const TFrequencyAnalyzer& analyzer) {
    if (this == &analyzer) {
        return *this;
    }
    _sl = analyzer._sl ? std::make_unique<TSignalLine>(*analyzer._sl) : nullptr;
    _params     = analyzer._params;
    _isExecuted = analyzer._isExecuted;
    return *this;
}

const TSignalLine* TFrequencyAnalyzer::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Fourier transform not executed");
    }
    return _sl.get();
}

const TFrequencyAnalyzerParams& TFrequencyAnalyzer::getParams() const {
    return _params;
}

bool TFrequencyAnalyzer::isExecuted() const {
    return _isExecuted;
}

void TFrequencyAnalyzer::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TFrequencyAnalyzer object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Invalid signal line (nullptr)");
    }
    if (!_params.signalLine->getParams().duration) {
        throw SignalProcessingError(
            "Signal line does not have duration information");
    }

    // Initialize frequency and time-related parameters
    const double fromFrequency = _params.fromFrequency;
    const double toFrequency   = _params.toFrequency;
    const double stepFrequency = _params.stepFrequency;
    const double duration = _params.signalLine->getParams().duration.value();
    const double samplingFreq =
        _params.signalLine->getParams().samplingFrequency.value();

    // Configure signal line parameters for the output frequency domain signal
    TSignalLineParams slParams = _params.signalLine->getParams();
    slParams.xLabel            = _params.xLabel;
    slParams.yLabel            = _params.yLabel;
    slParams.graphLabel        = _params.graphLabel;
    _sl                        = std::make_unique<TSignalLine>(
        ceil((toFrequency - fromFrequency) / stepFrequency));

    // Remove DC component from the signal
    auto DCRemovedSignal = TSignalLine(_params.signalLine);
    DCRemovedSignal.removeDCComponent();

    // Iterate through each frequency step and generate corresponding signal
    // data
    for (std::size_t i = 0; i < _sl->getParams().pointsCount; ++i) {
        // Set up generator parameters for a specific frequency
        TGeneratorParams genParams;
        genParams.duration = duration;
        genParams.oscillationFreq =
            fromFrequency + static_cast<double>(i) * stepFrequency;
        genParams.initPhase    = 0;
        genParams.offsetY      = 0;
        genParams.amplitude    = 1;
        genParams.samplingFreq = samplingFreq;

        // Create a generator and execute it to produce a signal for this
        // frequency
        TGenerator gen(genParams);
        gen.execute();

        // Correlate the generated signal with the original signal to compute
        // the correlation value
        TCorrelator corr(&DCRemovedSignal, gen.getSignalLine());
        corr.execute();

        _sl->setPoint(
            i, fromFrequency + static_cast<double>(i) * stepFrequency,
            _params.useAbsoluteValue.value_or(FA::DEFAULT_USE_ABSOLUTE_VALUE)
                ? std::abs(corr.getCorrelationValue())
                : corr.getCorrelationValue());
    }

    _isExecuted = true;
}