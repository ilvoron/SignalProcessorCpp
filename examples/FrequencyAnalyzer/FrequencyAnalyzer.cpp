/**
 * @file FrequencyAnalyzer.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Examples. Generating Noise and Performing Frequency Analysis.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TDifferentiator.hpp"
#include "TFileWriter.hpp"
#include "TFrequencyAnalyzer.hpp"
#include "TGenerator.hpp"
#include "TGnuPlotViewer.hpp"
#include "TNoiseGenerator.hpp"

int main() {
    // Generate a sine wave signal
    TGeneratorParams genParams;
    genParams.oscillationFreq = 524.0;  // 60 Hz sine wave
    genParams.amplitude       = 3.0;
    genParams.samplingFreq    = 10000.0;  // Sampling frequency
    TGenerator gen(genParams);
    gen.execute();

    // Generate noise signal
    TNoiseGeneratorParams noiseGenParams;
    noiseGenParams.signalLine     = gen.getSignalLine();
    noiseGenParams.noiseAmplitude = 1.0;
    noiseGenParams.noiseType      = NGEN::NoiseType::White;
    TNoiseGenerator noiseGenerator(noiseGenParams);
    noiseGenerator.execute();

    // Perform frequency analysis on the noise signal
    TFrequencyAnalyzerParams freqParams;
    freqParams.signalLine    = noiseGenerator.getSignalLine();
    freqParams.fromFrequency = 0;
    freqParams.toFrequency   = 1000;
    freqParams.stepFrequency = 0.25;
    TFrequencyAnalyzer freqAnalyzer(freqParams);
    freqAnalyzer.execute();

    // Writing the frequency analysis results
    TFileWriterParams writerParams;
    writerParams.filePath   = "noise_frequency_analysis.txt";
    writerParams.signalLine = freqAnalyzer.getSignalLine();
    TFileWriter writer(writerParams);
    writer.execute();

    // Plotting the frequency analysis results
    TGnuPlotViewerParams viewerParams;
    viewerParams.filePaths   = {writerParams.filePath};
    viewerParams.graphLabels = {{"Noise Frequency Spectrum"}};
    viewerParams.xLabel      = "Frequency (Hz)";
    viewerParams.yLabel      = "Normalized Correlation";
    TGnuPlotViewer viewer(viewerParams);
    viewer.execute();

    return 0;
}