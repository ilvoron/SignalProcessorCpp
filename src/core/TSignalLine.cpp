#include "TSignalLine.h"
#include <math.h>

// *************
//    PRIVATE
// *************

const double inaccuracy = 0.05;

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

// TODO: Make autodetect NULL values
TSignalLine::TSignalLine(double time, double samplingFreq) {
	_time = time;
	_oscillationFreq = NULL;
	_initPhase = NULL;
	_offsetY = NULL;
	_amplitude = NULL;
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

// TODO: Make it work with different initPhases (more than inaccuracy) + see also other files that using eqlals() method
// TODO: Make accuracy work when params are equal to 0
bool TSignalLine::equals(TSignalLine* sl) {
	double left, right;

	left = this->samplingFreq() * (1 - inaccuracy);
	right = this->samplingFreq() * (1 + inaccuracy);
	if (sl->samplingFreq() > left and sl->samplingFreq() < right) { return true; }
	else { return false; }

	left = this->time() * (1 - inaccuracy);
	right = this->time() * (1 + inaccuracy);
	if (sl->time() > left and sl->time() < right) { return true; }
	else { return false; }

	left = this->initPhase() * (1 - inaccuracy);
	right = this->initPhase() * (1 + inaccuracy);
	if (sl->initPhase() > left and sl->initPhase() < right) { return true; }
	else { return false; }
	
	return true;
}

unsigned int TSignalLine::pointsCount() { return _pointsCount; }
double TSignalLine::time() { return _time; }
double TSignalLine::oscillationFreq() { return _oscillationFreq; }
double TSignalLine::initPhase() { return _initPhase; }
double TSignalLine::offsetY() { return _offsetY; }
double TSignalLine::amplitude() { return _amplitude; }
double TSignalLine::samplingFreq() { return _samplingFreq; }