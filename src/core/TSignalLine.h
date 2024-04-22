#ifndef TSIGNALLINE_H
#define TSIGNALLINE_H

struct Point{
	double x;
	double y;
};

class TSignalLine{
	public:
		TSignalLine(double time, double oscillationFreq, double initPhase = 0, double offsetY = 0, double amplitude = 1, double samplingFreq = 1000);
		~TSignalLine();
		void set(unsigned int index, double x, double y);
		Point at(unsigned int index);
		unsigned int pointsCount();
		double time();
		double oscillationFreq();
		double initPhase();
		double offsetY();
		double amplitude();
		double samplingFreq();
	private:
		Point* _points;
		unsigned int _pointsCount;
		double _time;
		double _oscillationFreq;
		double _initPhase;
		double _offsetY;
		double _amplitude;
		double _samplingFreq;
};

#endif