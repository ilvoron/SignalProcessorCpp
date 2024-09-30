/**
 * TODO: Move differentiation logic to a separate method for each
 * differentiation method
 * TODO: Add switch-case for each differentiation method
 */

#include "TDifferentiator.h"
#include "TCore.h"
#include "TSignalLine.h"

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TDifferentiator::TDifferentiator(const TSignalLine* signalLine,
                                 bool performNormalization,
                                 std::string xLabel,
                                 std::string yLabel,
                                 std::string graphLabel,
                                 DifferentiationMethod method)
    : _params{signalLine,        performNormalization,  std::move(xLabel),
              std::move(yLabel), std::move(graphLabel), method} {}

TDifferentiator::TDifferentiator(TDifferentiatorParams params)
    : _params(std::move(params)) {}

const TSignalLine* TDifferentiator::getSignalLine() const {
  if (!_isExecuted) {
    throw SignalProcesserException("Differentiator not executed");
  }
  return _sl.get();
}

const TDifferentiatorParams& TDifferentiator::getParams() const {
  return _params;
}

bool TDifferentiator::isExecuted() const {
  return _isExecuted;
}

void TDifferentiator::execute() {
  if (_params.signalLine == nullptr) {
    throw SignalProcesserException("Invalid signal line (nullptr)");
  }
  if (_params.signalLine->getParams().pointsCount < 2) {
    throw SignalProcesserException("Insufficient number of points");
  }

  const bool centralOnly = _params.method == DifferentiationMethod::CentralOnly;
  const std::size_t pointsCountIn = _params.signalLine->getParams().pointsCount;
  const std::size_t pointsCountOut = pointsCountIn - (centralOnly ? 2 : 0);
  TSignalLineParams slParams = _params.signalLine->getParams();
  slParams.pointsCount = pointsCountOut;
  slParams.hasPointsCount = true;
  slParams.xLabel = _params.xLabel;
  slParams.yLabel = _params.yLabel;
  slParams.graphLabel = _params.graphLabel;
  _sl = std::make_unique<TSignalLine>(slParams);

  double deltaX = 0.0;
  double deltaY = 0.0;
  Point point1 = {0.0, 0.0};
  Point point2 = {0.0, 0.0};
  const double normalizeFactor =
      _params.performNormalization
          ? _params.signalLine->getParams().normalizeFactor
          : 1.0;
  for (std::size_t i = 1; i < pointsCountIn - 1; i++) {
    point1 = _params.signalLine->getPoint(i - 1);
    point2 = _params.signalLine->getPoint(i + 1);
    deltaX = point2.x - point1.x;
    deltaY = point2.y - point1.y;
    _sl->setPoint(i - (centralOnly ? 1 : 0), point1.x,
                  deltaY / deltaX / normalizeFactor);
  }

  if (!centralOnly) {
    point1 = _params.signalLine->getPoint(0);
    point2 = _params.signalLine->getPoint(1);
    deltaX = point2.x - point1.x;
    deltaY = point2.y - point1.y;
    _sl->setPoint(0, point1.x, deltaY / deltaX / normalizeFactor);

    point1 = _params.signalLine->getPoint(pointsCountIn - 2);
    point2 = _params.signalLine->getPoint(pointsCountIn - 1);
    deltaX = point2.x - point1.x;
    deltaY = point2.y - point1.y;
    _sl->setPoint(pointsCountIn - 1, point1.x,
                  deltaY / deltaX / normalizeFactor);
  }

  _isExecuted = true;
}