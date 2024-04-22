#ifndef TAMPLITUDEDETECTOR_H
#define TAMPLITUDEDETECTOR_H

#include "TSignalLine.h"

class TAmplitudeDetector {
public:
	TAmplitudeDetector(TSignalLine* sl);
	void exec();
	double amplitude() const;

private:
	TSignalLine* _sl;
	double _amplitude;
};

#endif