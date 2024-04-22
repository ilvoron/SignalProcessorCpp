#include "TAmplitudeDetector.h"
#include "TSignalLine.h"
#include "TMultiplier.h"
#include "TIntegral.h"
#include <math.h>

TAmplitudeDetector::TAmplitudeDetector(TSignalLine* sl) { _sl = sl; }

void TAmplitudeDetector::exec() {
	TMultiplier powerSignalLine(_sl, _sl);
	powerSignalLine.exec();
	TIntegral energy(powerSignalLine.sl());
	energy.exec();
	double power = energy.sum() / _sl->time();
	double voltage = sqrt(power);
	_amplitude = sqrt(2) * voltage;
}

double TAmplitudeDetector::amplitude() const { return _amplitude; }