#include "TSignalLine.h"
#include <math.h>

// ************
//    PUBLIC
// ************

TSignalLine::TSignalLine(double time, double oscillationFreq, double initPhase, double offsetY, double amplitude, double samplingFreq) {
	_time = time;
	_oscillationFreq = oscillationFreq;
	_initPhase = initPhase;
	_offsetY = offsetY;
	_amplitude = amplitude;
	_samplingFreq = samplingFreq;
	_pointsCount = ceil(time * samplingFreq);
	_points = new Point[_pointsCount];
}

TSignalLine::~TSignalLine(){ delete _points; }

void TSignalLine::set(unsigned int index,double x, double y){
	_points[index].x = x;
	_points[index].y = y;
}

Point TSignalLine::at(unsigned int index){ return _points[index]; }
unsigned int TSignalLine::pointsCount() { return _pointsCount; }
double TSignalLine::time() { return _time; }
double TSignalLine::oscillationFreq() { return _oscillationFreq; }
double TSignalLine::initPhase() { return _initPhase; }
double TSignalLine::offsetY() { return _offsetY; }
double TSignalLine::amplitude() { return _amplitude; }
double TSignalLine::samplingFreq() { return _samplingFreq; }