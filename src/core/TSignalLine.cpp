#include "TCore.h"
#include "TSignalLine.h"
#include <cmath>
#include <algorithm>

// PRIVATE

void TSignalLine::validatePointsInitialization() const {
	if (_points.empty()) THROW_SIGNAL_PROCESSOR_EXCEPTION("Points not initialized");
}

bool TSignalLine::areCloseX(const Point& point1, const Point& point2, double inaccuracy) const {
	double left = point1.x - inaccuracy;
	double right = point1.x + inaccuracy;
	if (point2.x >= left && point2.x <= right) return true;
	return false;
}

bool TSignalLine::areCloseY(const Point& point1, const Point& point2, double inaccuracy) const {
	double down = point1.y - inaccuracy;
	double up = point1.y + inaccuracy;
	if (point2.y >= down && point2.y <= up) return true;
	return false;
}

bool TSignalLine::areClose(const Point& point1, const Point& point2, double inaccuracy) const {
	return areCloseX(point1, point2, inaccuracy) && areCloseY(point1, point2, inaccuracy);
}

// PUBLIC

TSignalLine::TSignalLine(double time,
                         double oscillationFreq,
                         double initPhase,
                         double offsetY,
                         double amplitude,
                         double samplingFreq,
                         std::string xLabel,
                         std::string yLabel,
                         std::string graphLabel)
	: _params{static_cast<std::size_t>(ceil(time * samplingFreq)), time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq,
	          true, true, true, true, true, true, true,
	          xLabel, yLabel, graphLabel} {
		if (time <= 0) THROW_SIGNAL_PROCESSOR_EXCEPTION("Time should be positive");
		if (samplingFreq <= 0) THROW_SIGNAL_PROCESSOR_EXCEPTION("Sampling frequency should be positive");
		_points.resize(static_cast<size_t>(_params.pointsCount), Point{0.0, 0.0});
}

TSignalLine::TSignalLine(std::size_t pointsCount,
                         std::string xLabel,
                         std::string yLabel,
                         std::string graphLabel) {
	_params = {pointsCount, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
	           true, false, false, false, false, false, false,
	           xLabel, yLabel, graphLabel};
	_points.resize(pointsCount, Point{0.0, 0.0});
}

void TSignalLine::setPoint(std::size_t index, double x, double y) {
	validatePointsInitialization();
	_points.at(index).x = x;
	_points.at(index).y = y;
}

const Point& TSignalLine::getPoint(std::size_t index) const {
	validatePointsInitialization();
	return _points.at(index);
}

const TSignalLineParams& TSignalLine::getParams() const { return _params; }

bool TSignalLine::equals(const TSignalLine* signalLine, double inaccuracy) const {
	validatePointsInitialization();
	if (signalLine == nullptr) THROW_SIGNAL_PROCESSOR_EXCEPTION("TSignalLine pointer is null");
	signalLine->validatePointsInitialization();
	if (inaccuracy < 0) THROW_SIGNAL_PROCESSOR_EXCEPTION("Inaccuracy should be positive");
	
	TSignalLineParams paramsToCompare = signalLine->getParams();
	if (_params.pointsCount != paramsToCompare.pointsCount) { return false; }

	if (areCloseX(_points.at(0), signalLine->getPoint(0), inaccuracy) &&
		areCloseX(_points.at(_params.pointsCount - 1), signalLine->getPoint(_params.pointsCount - 1), inaccuracy)) { return true; }

	return false;
}