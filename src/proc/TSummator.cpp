/**
 * @file TSummator.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TSummator class for summing two
 * signal lines.
 * @version 2.1.0.2
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TSummator.hpp"
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

TSummator::TSummator(const TSignalLine*          signalLine1,
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

TSummator::TSummator(TSummatorParams params) : _params(std::move(params)) {}

TSummator::TSummator(const TSummator& summator)
    : _sl(summator._sl ? std::make_unique<TSignalLine>(*summator._sl)
                       : nullptr),
      _params(summator._params),
      _isExecuted(summator._isExecuted) {}

TSummator& TSummator::operator=(const TSummator& summator) {
    if (this == &summator) {
        return *this;
    }
    _sl = summator._sl ? std::make_unique<TSignalLine>(*summator._sl) : nullptr;
    _params     = summator._params;
    _isExecuted = summator._isExecuted;
    return *this;
}

const TSignalLine* TSummator::getSignalLine() const {
    if (!_isExecuted) {
        throw SignalProcessingError("Summator not executed");
    }
    return _sl.get();
}

const TSummatorParams& TSummator::getParams() const {
    return _params;
}

bool TSummator::isExecuted() const {
    return _isExecuted;
}

void TSummator::execute() {
    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TSummator object creation.
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
        yCoord = _params.signalLine1->getPoint(i).y +
                 _params.signalLine2->getPoint(i).y;
        _sl->setPoint(i, xCoord, yCoord);
    }

    _isExecuted = true;
}