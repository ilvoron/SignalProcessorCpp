#include "TCore.h"
#include "TGenerator.h"
#define _USE_MATH_DEFINES
#include <cmath>

const double TWO_PI = 2 * M_PI;

// PUBLIC

TGenerator::TGenerator(double time, double oscillationFreq, double initPhase, double offsetY, double amplitude, double samplingFreq, std::string xLabel, std::string yLabel, std::string graphLabel)
	: _sl(std::make_unique<TSignalLine>(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq, xLabel, yLabel, graphLabel)),
	  _params{time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq, xLabel, yLabel, graphLabel} {}

TGenerator::TGenerator(TGeneratorParams params)
	: _sl(std::make_unique<TSignalLine>(params.time, params.oscillationFreq, params.initPhase, params.offsetY, params.amplitude, params.samplingFreq, params.xLabel, params.yLabel, params.graphLabel)),
	  _params(params) {}

const TSignalLine* TGenerator::getSignalLine() const {
	if (!_isExecuted) THROW_SIGNAL_PROCESSOR_EXCEPTION("Generator not executed");
	return _sl.get();
}

const TGeneratorParams& TGenerator::getParams() const { return _params; }

bool TGenerator::isExecuted() const { return _isExecuted; }

void TGenerator::execute() {
	TSignalLineParams params = _sl->getParams();
	double x, y;
	double twoPiFreq = TWO_PI * params.oscillationFreq / params.samplingFreq;
	for (int i = 0; i < params.pointsCount; i++) {
		x = i / params.samplingFreq;
		y = params.amplitude * sin(twoPiFreq * i + params.initPhase) + params.offsetY;
		_sl->setPoint(i, x, y);
	}
	_isExecuted = true;
}