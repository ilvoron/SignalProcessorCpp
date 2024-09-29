#include "TIntegrator.h"
#include <cstddef>
#include "TCore.h"
#include "TSignalLine.h"

/**
 ** PUBLIC METHODS
 */

TIntegrator::TIntegrator(const TSignalLine* signalLine,
                         IntegrationMethod method)
    : _params{signalLine, method} {}

TIntegrator::TIntegrator(TIntegratorParams params) : _params(params) {}

double TIntegrator::getIntegral() const {
  if (!_isExecuted) {
    throw SignalProcesserException("Integrator not executed");
  }
  return _integral;
}

const TIntegratorParams& TIntegrator::getParams() const {
  return _params;
}

bool TIntegrator::isExecuted() const {
  return _isExecuted;
}

// TODO: Move integration logic to a separate method for each integration method
void TIntegrator::execute() {
  if (_params.signalLine == nullptr) {
    throw SignalProcesserException("Invalid signal line (nullptr)");
  }
  if (_params.signalLine->getParams().pointsCount < 2) {
    throw SignalProcesserException(
        "Insufficient number of points: at least 2 points are required");
  }

  const std::size_t pointsCount = _params.signalLine->getParams().pointsCount;
  _integral = 0.0;

  switch (_params.method) {
    case IntegrationMethod::Trapezoidal:
      for (size_t i = 1; i < pointsCount; ++i) {
        const double xCoordBefore = _params.signalLine->getPoint(i - 1).x;
        const double xCoord = _params.signalLine->getPoint(i).x;
        const double yCoordBefore = _params.signalLine->getPoint(i - 1).y;
        const double yCoord = _params.signalLine->getPoint(i).y;
        _integral += (yCoordBefore + yCoord) / 2.0 * (xCoord - xCoordBefore);
      }
      break;

    case IntegrationMethod::Simpson:
      if (pointsCount % 2 == 0) {
        throw SignalProcesserException(
            "Simpson's rule requires an odd number of points");
      }
      for (size_t i = 1; i < pointsCount - 1; i += 2) {
        const double xCoordBefore = _params.signalLine->getPoint(i - 1).x;
        const double xCoordNext = _params.signalLine->getPoint(i + 1).x;
        const double yCoordBefore = _params.signalLine->getPoint(i - 1).y;
        const double yCoord = _params.signalLine->getPoint(i).y;
        const double yCoordNext = _params.signalLine->getPoint(i + 1).y;
        _integral += (xCoordNext - xCoordBefore) / 6.0 *
                     (yCoordBefore + 4 * yCoord + yCoordNext);
      }
      break;

    case IntegrationMethod::Boole:
      if (pointsCount % 4 != 1) {
        throw SignalProcesserException(
            "Boole's rule requires number of points to be 4k + 1");
      }
      for (size_t i = 0; i < pointsCount - 4; i += 4) {
        const double xCoord = _params.signalLine->getPoint(i).x;
        const double xCoordNext4 = _params.signalLine->getPoint(i + 4).x;
        const double yCoord = _params.signalLine->getPoint(i).y;
        const double yCoordNext1 = _params.signalLine->getPoint(i + 1).y;
        const double yCoordNext2 = _params.signalLine->getPoint(i + 2).y;
        const double yCoordNext3 = _params.signalLine->getPoint(i + 3).y;
        const double yCoordNext4 = _params.signalLine->getPoint(i + 4).y;
        _integral += (xCoordNext4 - xCoord) / 90.0 *
                     (7 * yCoord + 32 * yCoordNext1 + 12 * yCoordNext2 +
                      32 * yCoordNext3 + 7 * yCoordNext4);
      }
      break;

    default:
      throw SignalProcesserException("Unknown integration method");
  }

  _isExecuted = true;
}