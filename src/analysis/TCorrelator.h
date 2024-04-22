#ifndef TCORRELATOR_H
#define TCORRELATOR_H

#include "TSignalLine.h"

class TCorrelator {
public:
	TCorrelator(TSignalLine* sl1, TSignalLine* sl2);
	void exec();
	double amplitude() const;

private:
	TSignalLine* _sl1;
	TSignalLine* _sl2;
	double _amplitude;
};

#endif