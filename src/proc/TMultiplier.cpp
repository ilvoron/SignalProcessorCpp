#include "TMultiplier.h"
#include "TCore.h"
#include "TSignalLine.h"

#include <memory>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TMultiplier::TMultiplier(const TSignalLine* signalLine1,
                         const TSignalLine* signalLine2,
                         double inaccuracy,
                         std::string xLabel,
                         std::string yLabel,
                         std::string graphLabel)
    : _params{signalLine1,       signalLine2,       inaccuracy,
              std::move(xLabel), std::move(yLabel), std::move(graphLabel)} {}

TMultiplier::TMultiplier(TMultiplierParams params)
    : _params(std::move(params)) {}

const TSignalLine* TMultiplier::getSignalLine() const {
  if (!_isExecuted) {
    throw SignalProcesserException("Multiplier not executed");
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
  if (_params.signalLine1 == nullptr || _params.signalLine2 == nullptr) {
    throw SignalProcesserException("Invalid signal lines (nullptr)");
  }
  if (!_params.signalLine1->equals(_params.signalLine2, _params.inaccuracy)) {
    throw SignalProcesserException("Signal lines aren't equal");
  }
  _sl = std::make_unique<TSignalLine>(
      _params.signalLine1->getParams().pointsCount, _params.xLabel,
      _params.yLabel, _params.graphLabel);
  double xCoord = 0.0;
  double yCoord = 0.0;
  for (int i = 0; i < _params.signalLine1->getParams().pointsCount; i++) {
    xCoord = _params.signalLine1->getPoint(i).x;
    yCoord =
        _params.signalLine1->getPoint(i).y * _params.signalLine2->getPoint(i).y;
    _sl->setPoint(i, xCoord, yCoord);
  }
  _isExecuted = true;
}