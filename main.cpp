#include "TSignalLine.h"
#include "TGenerator.h"
#include "TFileWriter.h"
#include "TGnuPlotViewer.h"

int main() {
	TGenerator gen;
	gen.execute();
	TFileWriter fw(gen.getSignalLine(), "sl.txt");
	fw.execute();

	TSignalLineParams params = gen.getSignalLine()->getParams();
	TGnuPlotViewer gpv("sl.txt", "gnuplot", params.xLabel, params.yLabel, params.graphLabel);
	gpv.execute();
}