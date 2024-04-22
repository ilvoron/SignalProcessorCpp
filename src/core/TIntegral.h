#ifndef TINTEGRAL_H
#define TINTEGRAL_H

#include "TIntegral.h"
#include "TSignalLine.h"

class TIntegral {
public:
	TIntegral(TSignalLine* sl);
	TSignalLine* sl() const;
	void exec();
	double sum() const;

private:
	TSignalLine* _sl_in;
	TSignalLine* _sl_out;
	double _sum;
};

#endif