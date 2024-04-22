#include "TFileWriter.h"
#include "TGenerator.h"

int main()
{
	double time = 3;
	double oscillationFreq = 2;
	double samplingFreq = 200;
	double amplitude = 3.5;
	double initPhase = 0;
	double offsetY = 0;
	TGenerator gen(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq);
	gen.exec();
	TFileWriter file(gen.sl(), "signal.txt");
	file.exec();
}
