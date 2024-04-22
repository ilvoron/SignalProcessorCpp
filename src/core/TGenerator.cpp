#include "TGenerator.h"
#include <math.h>

// *************
//    PRIVATE
// *************

int TGenerator::_randInt(int from, int to) {
	return rand() % (to - from + 1) + from;
}

// ************
//    PUBLIC
// ************

TGenerator::TGenerator(double time, double oscillationFreq, double initPhase, double offsetY, double amplitude, double samplingFreq) {
	_time = time;
	_oscillationFreq = oscillationFreq;
	_initPhase = initPhase;
	_offsetY = offsetY;
	_amplitude = amplitude;
	_samplingFreq = samplingFreq;
	_sl = new TSignalLine(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq);
}

TSignalLine *TGenerator::sl() const { return _sl; }

void TGenerator::exec() {
	unsigned int pointsCount = _sl->pointsCount();
	double x, y;
	for (int i = 0; i < pointsCount; i++) {
		x = i / _samplingFreq;
		y = _amplitude * sin((2 * i * M_PI * _oscillationFreq) / _samplingFreq + _initPhase) + _offsetY;
		_sl->set(i, x, y);
	}
}

// TODO: MAKE "TRUE" NOISE WITH TOTAL ABS EQUALS TO 0 + REFACTOR THE FUNCTION
void TGenerator::addNoise(double dispersion){
	for (int i = 0;i<_sl->pointsCount();i++){
		double yOffset = _randInt(1, 1000000) / 1000000. * dispersion;
		int modif = _randInt(0, 2) - 1;
		_sl->set(i,_sl->at(i).x,_sl->at(i).y + modif * yOffset);
	}
}