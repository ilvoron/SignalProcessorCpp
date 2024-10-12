# Signal Processing Library (SignalProcessorCPP)

This project provides a set of classes for signal generation, processing, noise
application, numerical integration, file I/O, and visualization using GnuPlot.
It is designed for handling basic signal processing tasks, managing signal
parameters, and visualizing signals in a clear and flexible way.

## Features

- **Signal Generation**: Generate customizable signal lines with adjustable
  parameters, such as time duration, frequency, amplitude, and phase.
- **Signal Line Manipulation**: Set, retrieve, compare, and manipulate
  individual points of the signal.
- **Signal Summation and Multiplication**: Add and multiply signal lines point
  by point.
- **Signal Differentiation and Integration**: Perform numerical differentiation
  and integration of signals.
- **Noise Generation**: Add configurable noise to signal lines.
- **File I/O**: Save generated or modified signal lines to files and load them
  for further processing.
- **GnuPlot Visualization**: Visualize signal data using GnuPlot with
  configurable axis and graph labels.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/ilvoron/SignalProcessorCPP
   cd SignalProcessorCPP
   ```

2. Build the project (assuming a C++ compiler, `cmake`, and `make` are
   installed):

   ```bash
   cd "_build_folder_"
   cmake -G "_generator_name_" "_path_to_main_cmake_lists_file_"
   make
   ```

3. Ensure you have [GnuPlot](http://www.gnuplot.info/) installed on your system
   for visualization functionality.

## Usage

### Signal Generation Example

```cpp
#include "TGenerator.h"
#include "TFileWriter.h"

int main() {
    // Set up generator parameters
    TGeneratorParams params;
    params.time = 5.0;
    params.oscillationFreq = 2.0;
    params.amplitude = 3.0;

    // Generate the signal
    TGenerator generator(params);
    generator.execute();

    // Save the signal to a file
    TFileWriter writer(generator.getSignalLine(), "output_signal.txt");
    writer.execute();

    return 0;
}
```

### Signal Summation Example

```cpp
#include "TSummator.h"
#include "TGenerator.h"

int main() {
    // Set up generator parameters for signal 1
    TGeneratorParams params1;
    params1.time = 5.0;
    params1.oscillationFreq = 2.0;
    params1.amplitude = 3.0;
    params1.samplingFreq = 100.0;

    // Set up generator parameters for signal 2
    TGeneratorParams params2;
    params2.time = 5.0;
    params2.oscillationFreq = 1.0;
    params2.amplitude = 2.0;
    params2.samplingFreq = 100.0;

    // Create two signal generators
    TGenerator generator1(params1);
    TGenerator generator2(params2);

    // Execute the generation process
    generator1.execute();
    generator2.execute();

    // Sum the two signals
    TSummator summator(generator1.getSignalLine(), generator2.getSignalLine());
    summator.execute();

    const TSignalLine* summedSignal = summator.getSignalLine();

    // ...
    // Use summedSignal as needed
    // ...

    return 0;
}
```

### Signal Differentiation Example

```cpp
#include "TDifferentiator.h"
#include "TGenerator.h"

int main() {
    // Set up generator parameters
    TGeneratorParams params;
    params.time = 5.0;
    params.oscillationFreq = 2.0;
    params.amplitude = 3.0;
    params.samplingFreq = 100.0;

    // Generate the signal
    TGenerator generator(params);
    generator.execute();

    // Differentiate the generated signal
    TDifferentiator differentiator(generator.getSignalLine());
    differentiator.execute();

    const TSignalLine* diffSignal = differentiator.getSignalLine();

    // ...
    // Use diffSignal as needed
    // ...

    return 0;
}
```

### Noise Generation Example

```cpp
#include "TNoiseGenerator.h"
#include "TGenerator.h"

int main() {
    // Set up generator parameters
    TGeneratorParams params;
    params.time = 5.0;
    params.oscillationFreq = 2.0;
    params.amplitude = 3.0;
    params.samplingFreq = 100.0;

    // Generate the signal
    TGenerator generator(params);
    generator.execute();

    // Add noise to the generated signal
    TNoiseGenerator noiseGen(generator.getSignalLine(), 0.3);
    noiseGen.execute();

    const TSignalLine* noisySignal = noiseGen.getSignalLine();

    // ...
    // Use noisySignal as needed
    // ...

    return 0;
}
```

### Visualization Example with GnuPlot

```cpp
#include "TGnuPlotViewer.h"
#include "TFileWriter.h"
#include "TGenerator.h"

int main() {
    // Set up generator parameters
    TGeneratorParams params;
    params.time = 5.0;
    params.oscillationFreq = 2.0;
    params.amplitude = 3.0;
    params.samplingFreq = 100.0;

    // Generate the signal
    TGenerator generator(params);
    generator.execute();

    // Save the generated signal to a file
    TFileWriter writer(generator.getSignalLine(), "output_signal.txt");
    writer.execute();

    // Visualize the saved signal using GnuPlot
    TGnuPlotViewer viewer("output_signal.txt", "Time (s)", "Amplitude", "Generated Signal", "/usr/bin/gnuplot");
    viewer.execute();

    return 0;
}
```

## Dependencies

- **C++20** or higher
- **GnuPlot**: Required for signal visualization
- **CMake** & **Make**: For building the project

## License

This project is licensed under the MIT License. See the
[LICENSE.md](./LICENSE.md) file for details.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

---

## Classes Overview

- **SignalProcessingError** - Custom exception class for handling errors
  during signal processing.
- **TSignalLine** - Represents a signal line made up of multiple points. It
  manages signal parameters such as time duration, frequency, amplitude, and
  phase. You can set, retrieve, and compare individual points.
- **TGenerator** - Generates a signal line based on given parameters. It
  supports execution of the signal generation process and provides access to the
  generated signal.
- **TSummator** - Sums two signal lines point by point, with optional tolerance
  for inaccuracy.
- **TMultiplier** - Multiplies two signal lines point by point.
- **TDifferentiator** - Differentiates a signal line using either central
  differences or a combination of central and one-sided differences.
- **TIntegrator** - Performs numerical integration of a signal line using the
  Trapezoidal, Simpson, or Boole methods.
- **TNoiseGenerator** - Adds configurable white noise to a signal line.
- **TFileWriter** - Saves a signal line to a file.
- **TGnuPlotViewer** - Visualizes the signal data using GnuPlot.
