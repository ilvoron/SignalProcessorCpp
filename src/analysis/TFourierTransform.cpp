#include "TFourierTransform.h"
#include "TSignalLine.h"
#include "TMultiplier.h"
#include "TIntegral.h"
#include "TCorrelator.h"
#include "TGenerator.h"
#include <math.h>
#include <stdexcept>

TFourierTransform::TFourierTransform(TSignalLine* sl, double from, double to, double step) {
	// TODD: Fix error output (text should constant and be stored somewhere)
	// TODO: Should be there an error?
	if (from > to) { throw std::runtime_error("From is bigger than to"); }
	_from = from;
	_to = to;
	_step = step;
	_sl_in = sl;
	_sl_out = new TSignalLine(int((to - from) / step));
}

TSignalLine* TFourierTransform::sl() const { return _sl_out; }

void TFourierTransform::exec() {
	unsigned int counter = 0;
	for (double i = _from; i < _to; i = i + _step) {
		TGenerator gen(_sl_in->time(), i, 0, 0, 1, _sl_in->samplingFreq());
		gen.exec();
		TCorrelator corr = TCorrelator(_sl_in, gen.sl());
		corr.exec();
		_sl_out->set(counter, i, corr.amplitude());
		counter++;
	}
}