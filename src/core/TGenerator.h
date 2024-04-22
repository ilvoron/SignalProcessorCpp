#ifndef TGENERATOR_H
#define TGENERATOR_H

#include <cmath>
#include "TSignalLine.h"

class TGenerator{
	public:
		TGenerator(double time, double oscillationFreq, double initPhase = 0, double offsetY = 0, double amplitude = 1, double samplingFreq = 1000);
		TSignalLine *sl() const;
		void exec();
		void addNoise(double dispersion);
	private:
		TSignalLine* _sl;
		double _time;
		double _oscillationFreq;
		double _initPhase;
		double _offsetY;
		double _amplitude;
		double _samplingFreq;
		int _randInt(int from, int to);
};

#endif