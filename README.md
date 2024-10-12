# Signal Processing Library (Toolkit) - `SignalProcessorCPP`

This project provides a comprehensive set of tools for digital signal processing (DSP), including classes for
generating, manipulating, and analyzing signals in both time and frequency domains. The toolkit is designed with
flexibility and efficiency in mind, making it suitable for various DSP tasks, such as waveform generation, noise
addition, amplitude detection, differentiation, integration, and frequency analysis.

## Key Features

### 1. Signal Management and Manipulation

- `TSignalLine` - Represents a general signal line with methods for managing and processing signal data points.

### 2. Signal Generation

- `TGenerator` - Generates waveforms such as sine, cosine, tangent, and cotangent with customizable parameters like
  frequency, amplitude, and phase.
- `TNoiseGenerator` - Adds noise to signals with configurable noise characteristics.

### 3. Signal Processing

- `TAmplitudeDetector` - Computes the amplitude of a signal by removing the DC component and applying the RMS module.
- `TDifferentiator` - Calculates the derivative of a signal using various differentiation methods.
- `TIntegrator` - Computes the integral of a signal with selectable integration methods (e.g., trapezoidal, Simpson’s).
- `TMultiplier` and `TSummator` - Perform pointwise multiplication and summation of two signals, respectively.

### 4. Root Mean Square and Correlation

- `TRMS` - Computes the RMS value of a signal, which is a measure of the signal's power.
- `TCorrelator` - Computes the correlation factor between two signals. Normalizes the correlation using RMS values to
  obtain a normalized correlation coefficient.

### 5. Frequency Analysis

- `TFrequencyAnalyzer` - Converts a signal from the time domain to the frequency domain by correlating it with
  sinusoidal
  signals. Removes the DC component automatically to provide an accurate frequency analysis.

### 6. File Output and Visualization

- `TFileWriter` - Saves signals to text files, with an option to overwrite existing files.
- `TGnuPlotViewer` - Provides tools for visualizing signals using GnuPlot with configurable options for graph
  presentation.

## Technical Details

- **Doxygen Documentation**: All classes and methods are documented with Doxygen comments for easy reference and
  understanding.

## Getting Started

### Prerequisites

- C++20 or higher.
- GnuPlot: Required for signal visualization.
- CMake & Make: For building the project.

### Installation

Clone the repository and build the project with CMake:

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
mkdir build && cd build
cmake ..
make
```

## Examples

See the `examples` directory for sample code snippets demonstrating the usage of the toolkit classes.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.