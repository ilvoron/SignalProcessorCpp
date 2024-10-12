/**
 * @file TCorrelator.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TCorrelator class correlating
 * two signal lines generation.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TCorrelator.hpp"
#include "TCore.hpp"
#include "TIntegrator.hpp"
#include "TMultiplier.hpp"
#include "TRMS.hpp"
#include "TSignalLine.hpp"

#include <optional>

/*
 * PUBLIC METHODS
 */

TCorrelator::TCorrelator(const TSignalLine*        signalLine1,
                         const TSignalLine*        signalLine2,
                         const std::optional<bool> performNormalization)
    : _params{.signalLine1          = signalLine1,
              .signalLine2          = signalLine2,
              .performNormalization = performNormalization} {}

TCorrelator::TCorrelator(const TCorrelatorParams& params) : _params(params) {}

double TCorrelator::getCorrelationValue() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Correlator not executed");
    }
    return _correlationValue;
}

const TCorrelatorParams& TCorrelator::getParams() const {
    return _params;
}

bool TCorrelator::isExecuted() const {
    return _isExecuted;
}

void TCorrelator::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TCorrelator object creation.
    if (_params.signalLine1 == nullptr || _params.signalLine2 == nullptr) {
        throw SignalProcessingError("Invalid signal line (nullptr)");
    }
    if (!_params.signalLine1->getParams().duration ||
        !_params.signalLine2->getParams().duration) {
        throw SignalProcessingError(
            "Signal line does not have duration information");
    }

    // Create the product signal for correlation
    TMultiplier productSignal(_params.signalLine1, _params.signalLine2);
    productSignal.execute();

    // Integrate the product signal to calculate the raw correlation value
    TIntegrator integratedCorrelation(productSignal.getSignalLine());
    integratedCorrelation.execute();
    const double rawCorrelation =
        integratedCorrelation.getIntegral() /
        _params.signalLine1->getParams().duration.value();

    if (_params.performNormalization.value_or(
            COR::DEFAULT_PERFORM_NORMALIZATION)) {
        // --> Using RMS to calculate the normalized value <--

        // Calculate the RMS values for both signals
        TRMS rms1(_params.signalLine1);
        rms1.execute();
        TRMS rms2(_params.signalLine2);
        rms2.execute();

        // Normalize the correlation by the product of RMS values
        _correlationValue =
            rawCorrelation / (rms1.getRMSValue() * rms2.getRMSValue());
    } else {
        _correlationValue = rawCorrelation;
    }

    _isExecuted = true;
}