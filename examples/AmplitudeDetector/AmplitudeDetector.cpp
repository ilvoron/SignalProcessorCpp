/**
 * @file AmplitudeDetector.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Examples. Generating a Sine Wave and Detecting its Amplitude.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TGenerator.hpp"
#include "TAmplitudeDetector.hpp"
#include <iostream>

int main() {
    // Generate a sine wave signal
    TGeneratorParams genParams;
    genParams.oscillationFreq = 60.0;  // 60 Hz sine wave
    genParams.amplitude       = 3.0;
    genParams.samplingFreq    = 1000.0;  // Sampling frequency
    TGenerator gen(genParams);
    gen.execute();

    // Detect amplitude of the generated signal
    TAmplitudeDetectorParams ampDetParams;
    ampDetParams.signalLine = gen.getSignalLine();
    TAmplitudeDetector ampDet(ampDetParams);
    ampDet.execute();
    std::cout << "Amplitude of sine wave: " << ampDet.getAmplitude() << std::endl;

    return 0;
}
