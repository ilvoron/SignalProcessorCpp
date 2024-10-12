/**
 * @file TAmplitudeDetector.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TAmplitudeDetector class for
 * detecting the amplitude of a signal.
 * @version 2.1.0.1
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TAmplitudeDetector.hpp"
#include "TCore.hpp"
#include "TRMS.hpp"
#include "TSignalLine.hpp"

#include <numbers>

/*
 * PUBLIC METHODS
 */

TAmplitudeDetector::TAmplitudeDetector(const TSignalLine* signalLine)
    : _params{signalLine} {}

TAmplitudeDetector::TAmplitudeDetector(const TAmplitudeDetectorParams& params)
    : _params(params) {}

double TAmplitudeDetector::getAmplitude() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Amplitude detector not executed");
    }
    return _amplitude;
}

const TAmplitudeDetectorParams& TAmplitudeDetector::getParams() const {
    return _params;
}

bool TAmplitudeDetector::isExecuted() const {
    return _isExecuted;
}

void TAmplitudeDetector::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TFileWriter object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Signal line is not specified.");
    }
    if (!_params.signalLine->getParams().duration) {
        throw SignalProcessingError(
            "Signal line does not have duration information");
    }

    // --> Using RMS to calculate the amplitude <--

    // Remove DC component from the signal
    auto DCRemovedSignal = TSignalLine(_params.signalLine);
    DCRemovedSignal.removeDCComponent();

    // Calculate RMS value.
    TRMS rms(&DCRemovedSignal);
    rms.execute();

    // Calculate amplitude based on RMS
    _amplitude = std::numbers::sqrt2 * rms.getRMSValue();

    _isExecuted = true;
}