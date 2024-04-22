#include "TIntegral.h"
#include "TSignalLine.h"

TIntegral::TIntegral(TSignalLine* sl) {
	_sl_in = sl;
	_sl_out = new TSignalLine(_sl_in->time(), _sl_in->samplingFreq(), _sl_in->pointsCount());
	_sum = 0;
}

TSignalLine* TIntegral::sl() const { return _sl_out; }

void TIntegral::exec() {
	unsigned int pointsCount = _sl_out->pointsCount();
	double x1, x2, y, sum;
	for (int i = 1; i < pointsCount; i++) {
		x1 = (_sl_in->at(i-1)).x;
		x2 = (_sl_in->at(i)).x;
		y = (_sl_in->at(i)).y;
		_sum += y * (x2 - x1);
		_sl_out->set(i, (_sl_in->at(i)).x, _sum);
	}
}

double TIntegral::sum() const { return _sum; }