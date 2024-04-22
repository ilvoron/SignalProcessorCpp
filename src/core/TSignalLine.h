#ifndef TSIGNALLINE_H
#define TSIGNALLINE_H

struct Point{
	double x;
	double y;
};

class TSignalLine{
	public:
		// TODO: Make default params
		TSignalLine(double time, double oscillationFreq, double initPhase, double offsetY, double amplitude, double samplingFreq);
		TSignalLine(double time, double samplingFreq, unsigned int pointsCount);
		TSignalLine(double time, double samplingFreq);
		TSignalLine(unsigned int pointsCount);
		~TSignalLine();
		void set(unsigned int index, double x, double y);
		Point at(unsigned int index);
		bool equals(TSignalLine* sl);
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