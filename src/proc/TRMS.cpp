/**
 * @file TRMS.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TRMS class for calculating the RMS
 * value (Root Mean Square) of a signal.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TRMS.hpp"
#include "TCore.hpp"
#include "TIntegrator.hpp"
#include "TMultiplier.hpp"
#include "TSignalLine.hpp"

#include <cmath>
#include <optional>

/*
 * PUBLIC METHODS
 */

TRMS::TRMS(const TSignalLine*          signalLine,
           const std::optional<double> inaccuracy)
    : _params{.signalLine = signalLine, .inaccuracy = inaccuracy} {}

TRMS::TRMS(const TRMSParams& params) : _params(params) {}

double TRMS::getRMSValue() const {
    if (!_isExecuted) {
        throw SignalProcessingError("RMS not executed");
    }
    return _rmsValue;
}

const TRMSParams& TRMS::getParams() const {
    return _params;
}

bool TRMS::isExecuted() const {
    return _isExecuted;
}

void TRMS::execute() {
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Signal line is not specified.");
    }
    if (!_params.signalLine->getParams().duration) {
        throw SignalProcessingError(
            "Signal line does not have duration information");
    }

    // Create squared signal for power calculation
    TMultiplier squaredSignal(_params.signalLine, _params.signalLine);
    squaredSignal.execute();

    // Integrate power to obtain the total energy of the signal
    TIntegrator totalPower(squaredSignal.getSignalLine());
    totalPower.execute();

    // Calculate mean power and RMS Value
    const double meanPower = totalPower.getIntegral() /
                             _params.signalLine->getParams().duration.value();
    _rmsValue = sqrt(meanPower);

    _isExecuted = true;
}
