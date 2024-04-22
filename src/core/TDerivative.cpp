#include "TDerivative.h"
#include "TSignalLine.h"

TDerivative::TDerivative(TSignalLine* sl) {
	_sl_in = sl;
	_sl_out = new TSignalLine(_sl_in->time(), _sl_in->samplingFreq(), _sl_in->pointsCount());
}

TSignalLine* TDerivative::sl() const { return _sl_out; }

void TDerivative::exec() {
	unsigned int pointsCount = _sl_out->pointsCount();
	double dx, dy;
	for (int i = 0; i < pointsCount; i++) {
		dy = (_sl_in->at(i+1)).y - (_sl_in->at(i)).y;
		dx = (_sl_in->at(i+1)).x - (_sl_in->at(i)).x;
		_sl_out->set(i, (_sl_in->at(i)).x, dy/dx);
	}
}