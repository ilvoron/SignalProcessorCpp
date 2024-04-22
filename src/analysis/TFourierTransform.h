#ifndef TFOURIERTRANSFORM_H
#define TFOURIERTRANSFORM_H

#include "TSignalLine.h"

class TFourierTransform {
public:
	TFourierTransform(TSignalLine* sl, double from, double to, double step);
	TSignalLine* sl() const;
	void exec();

private:
	TSignalLine* _sl_in;
	TSignalLine* _sl_out;
	double _from;
	double _to;
	double _step;
};

#endif