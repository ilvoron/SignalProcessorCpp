#include "TCore.h"
#include "TSignalLine.h"
#include <cmath>

// PRIVATE

void TSignalLine::validatePointsInitialization() const {
	if (_points.empty()) THROW_SIGNAL_PROCESSOR_EXCEPTION("Points not initialized");
}

// PUBLIC

TSignalLine::TSignalLine(double time,
                         double oscillationFreq,
						 double initPhase,
						 double offsetY,
						 double amplitude,
						 double samplingFreq)
	: _params{static_cast<std::size_t>(ceil(time * samplingFreq)), time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq,
			  true, true, true, true, true, true, true} {
		if (time <= 0) THROW_SIGNAL_PROCESSOR_EXCEPTION("Time should be positive");
		if (samplingFreq <= 0) THROW_SIGNAL_PROCESSOR_EXCEPTION("Sampling frequency should be positive");
		_points.resize(static_cast<size_t>(_params.pointsCount), Point{0.0, 0.0});
}

void TSignalLine::setPoint(unsigned int index, double x, double y) {
	validatePointsInitialization();
	_points[index].x = x;
	_points[index].y = y;
}

const Point& TSignalLine::getPoint(unsigned int index) const {
	validatePointsInitialization();
	return _points[index];
}

const TSignalLineParams& TSignalLine::getParams() const {
	if (!_params.pointsCount) THROW_SIGNAL_PROCESSOR_EXCEPTION("Parameters not initialized");
	return _params;
}