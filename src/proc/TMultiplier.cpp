/**
 * @file TMultiplier.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TMultiplier class for multiplying
 * two signal lines.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo Product of two different signals: end multiplication if one of the
 * signals ends OR add ones (or zeros?) to the end of the shorter signal
 */

#include "TMultiplier.hpp"
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TMultiplier::TMultiplier(const TSignalLine*          signalLine1,
                         const TSignalLine*          signalLine2,
                         const std::optional<double> inaccuracy,
                         std::optional<std::string>  xLabel,
                         std::optional<std::string>  yLabel,
                         std::optional<std::string>  graphLabel)
    : _params{.signalLine1 = signalLine1,
              .signalLine2 = signalLine2,
              .inaccuracy  = inaccuracy,
              .xLabel      = std::move(xLabel),
              .yLabel      = std::move(yLabel),
              .graphLabel  = std::move(graphLabel)} {}

TMultiplier::TMultiplier(TMultiplierParams params)
    : _params(std::move(params)) {}

TMultiplier::TMultiplier(const TMultiplier& multiplier)
    : _sl(multiplier._sl ? std::make_unique<TSignalLine>(*multiplier._sl)
                         : nullptr),
      _params(multiplier._params),
      _isExecuted(multiplier._isExecuted) {}

TMultiplier& TMultiplier::operator=(const TMultiplier& multiplier) {
    if (this == &multiplier) {
        return *this;
    }
    _sl     = multiplier._sl ? std::make_unique<TSignalLine>(*multiplier._sl)
                             : nullptr;
    _params = multiplier._params;
    _isExecuted = multiplier._isExecuted;
    return *this;
}

const TSignalLine* TMultiplier::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Multiplier not executed");
    }
    return _sl.get();
}

const TMultiplierParams& TMultiplier::getParams() const {
    return _params;
}

bool TMultiplier::isExecuted() const {
    return _isExecuted;
}

void TMultiplier::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TMultiplier object creation.
    if (_params.signalLine1 == nullptr || _params.signalLine2 == nullptr) {
        throw SignalProcessingError("Invalid signal lines (nullptr)");
    }
    if (!_params.signalLine1->equals(_params.signalLine2, _params.inaccuracy)) {
        throw SignalProcessingError("Signal lines aren't equal");
    }

    TSignalLineParams slParams = _params.signalLine1->getParams();
    slParams.xLabel            = _params.xLabel;
    slParams.yLabel            = _params.yLabel;
    slParams.graphLabel        = _params.graphLabel;
    _sl                        = std::make_unique<TSignalLine>(slParams);

    double xCoord = 0.0;
    double yCoord = 0.0;
    for (std::size_t i = 0; i < _params.signalLine1->getParams().pointsCount;
         ++i) {
        xCoord = _params.signalLine1->getPoint(i).x;
        yCoord = _params.signalLine1->getPoint(i).y *
                 _params.signalLine2->getPoint(i).y;
        _sl->setPoint(i, xCoord, yCoord);
    }

    _isExecuted = true;
}