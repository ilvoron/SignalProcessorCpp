#include <math.h>
#include <stdexcept>
#include "TCorrelator.h"
#include "TSignalLine.h"
#include "TMultiplier.h"
#include "TIntegral.h"

TCorrelator::TCorrelator(TSignalLine* sl1, TSignalLine* sl2) {
	// TODO: Fix equals (see TSignalLine)
	// TODD: Fix error output (text should constant and be stored somewhere)
	if (!(sl1->equals(sl2))) { throw std::runtime_error("Signals does not have minimum equal params"); }
	_sl1 = sl1;
	_sl2 = sl2;
}

void TCorrelator::exec() {
	TMultiplier powerSignalLine(_sl1, _sl2);
	powerSignalLine.exec();
	TIntegral energy(powerSignalLine.sl());
	energy.exec();
	double power = energy.sum() / _sl1->time();
	double voltage = abs(power);
	_amplitude = 2 * voltage;
}

double TCorrelator::amplitude() const { return _amplitude; }