#include "TFileWriter.h"
#include "TGenerator.h"
#include "TSummator.h"

int main() {
	// EXAMPLE CODE
	double time = 3;
	double oscillationFreq = 2;
	double samplingFreq = 200;
	double amplitude = 3.5;
	double initPhase = 0;
	double offsetY = 0;
	TGenerator gen1(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq);
	TGenerator gen2(time+0.1, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq+5);
	gen1.exec();
	gen2.exec();
	TSummator sum(gen1.sl(), gen2.sl());
	sum.exec();
	TFileWriter file(sum.sl(), "signal.txt");
	file.exec();
}
