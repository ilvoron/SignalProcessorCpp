#include "TFileWriter.h"
#include "TSignalLine.h"
#include "TGenerator.h"
#include "TSummator.h"
#include "TMultiplier.h"
#include "TDerivative.h"
#include "TIntegral.h"
#include "TAmplitudeDetector.h"
#include "TCorrelator.h"
#include "TFourierTransform.h"

int main() {
	// EXAMPLE CODE
	double time = 3;
	double oscillationFreq = 4.5612;
	double samplingFreq = 200;
	double amplitude = 3.5;
	double initPhase = 0;
	double offsetY = 0;
	TGenerator gen1(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq);
	TGenerator gen2(time, oscillationFreq*1.66, initPhase, offsetY, amplitude-1, samplingFreq);
	gen1.exec();
	gen2.exec();
	TSummator sum(gen1.sl(), gen2.sl());
	sum.exec();
	TFourierTransform trans(sum.sl(), 0, 10, 0.01);
	trans.exec();
	TFileWriter file1(trans.sl(), "fourier.txt");
	TFileWriter file2(sum.sl(), "signal.txt");
	file1.exec();
	file2.exec();
	/*double time = 3;
	double oscillationFreq = 2;
	double samplingFreq = 200;
	double amplitude = 3.5;
	double initPhase = 0;
	double offsetY = 0;
	TGenerator gen1(time, oscillationFreq, initPhase, offsetY, amplitude, samplingFreq);
	TGenerator gen2(time, oscillationFreq / 0.66, initPhase, offsetY, amplitude, samplingFreq+5);
	gen1.exec();
	gen2.exec();
	TMultiplier mult1(gen1.sl(), gen2.sl());
	TMultiplier mult2(gen1.sl(), gen1.sl());
	mult1.exec();
	mult2.exec();
	TFileWriter file1(mult1.sl(), "signalDiff.txt");
	TFileWriter file2(mult2.sl(), "signalEq.txt");
	file1.exec();
	file2.exec();*/
}
