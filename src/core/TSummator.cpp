#include <stdexcept>
#include "TSummator.h"
#include "TSignalLine.h"

TSummator::TSummator(TSignalLine* sl1, TSignalLine* sl2) {
	// TODO: Fix equals (see TSignalLine)
	if (!(sl1->equals(sl2))) { throw std::runtime_error("Signals does not have minimum equal params"); }
	_sl1 = sl1;
	_sl2 = sl2;
	_sl = new TSignalLine(sl1->time(), sl1->samplingFreq());
}

void TSummator::exec() {
	unsigned int pointsCount = _sl->pointsCount();
	double x, y;
	for (int i = 0; i < pointsCount; i++) {
		// TODO: After fix equls use approx. value for x (if it needs)
		x = (_sl1->at(i)).x;
		y = (_sl1->at(i)).y + (_sl2->at(i)).y;
		_sl->set(i, x, y);
	}
}

TSignalLine* TSummator::sl() const {
	return _sl;
}