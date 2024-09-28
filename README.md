# Signal Processing Library (SignalProcesserCPP)

This project provides a set of classes for signal generation, processing, file I/O, and visualization using GnuPlot. It is designed for handling basic signal processing tasks, managing signal parameters, and visualizing signals in a clear and flexible way.

## Features

-   **Signal Generation**: Generate customizable signal lines with adjustable frequency, amplitude, phase, and more.
-   **Signal Line Manipulation**: Modify and retrieve individual points of the signal.
-   **File I/O**: Save generated signal lines to files and load them for further processing.
-   **GnuPlot Visualization** (must be pre-installed): Easily visualize signal data using GnuPlot with configurable axis and graph labels.
-   **Custom Exception Handling**: Handle errors in signal processing with detailed exception messages.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/ilvoron/SignalProcesserCPP
    cd SignalProcesserCPP
    ```

2. Build the project (assuming a C++ compiler, `cmake` and `make` are installed):

    ```bash
    cd "_build_folder_"
    cmake -G "_generator_name_" "_path_to_main_cmake_lists_file_"
    make
    ```

3. Ensure you have [GnuPlot](http://www.gnuplot.info/) installed on your system for visualization functionality.

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

### Visualization Example with GnuPlot

```cpp
#include "TGnuPlotViewer.h"

int main() {
    // Set up visualization parameters and execute GnuPlot
    TGnuPlotViewer viewer("output_signal.txt", "/usr/bin/gnuplot", "Time (s)", "Amplitude", "Generated Signal");
    viewer.execute();

    return 0;
}
```

## Dependencies

-   **C++20** or higher
-   **GnuPlot**: Required for signal visualization
-   **CMake** & **Make**: For building the project

## License

This project is licensed under the MIT License. See the [LICENSE.md](./LICENSE.md) file for details.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Feel free to adjust this template to better reflect your project's structure and the specific functionality you offer.

---

## Classes Overview

-   **SignalProcesserException** - Custom exception class for handling errors during signal processing. It includes additional details like the function name where the error occurred.
-   **TSignalLine** - Represents a signal line made up of multiple points. Parameters such as frequency, amplitude, and phase can be customized. You can set, retrieve, and manipulate individual points in the signal.
-   **TGenerator** - Generates a signal line based on given parameters. The class supports execution of the signal generation process and provides access to the generated signal line.
-   **TFileWriter** - Responsible for writing signal data to a file. Accepts a signal line and a file path and saves the signal data in a specified format.
-   **TGnuPlotViewer** - Visualizes the signal data using GnuPlot. You can configure the file path, axis labels, and graph labels, and execute GnuPlot to render the graph.
