# Classes Overview
- SignalProcesserException - Custom exception class for handling errors during signal processing. It includes additional details like the function name where the error occurred.
- TSignalLine - Represents a signal line made up of multiple points. Parameters such as frequency, amplitude, and phase can be customized. You can set, retrieve, and manipulate individual points in the signal.
- TGenerator - Generates a signal line based on given parameters. The class supports execution of the signal generation process and provides access to the generated signal line.
- TFileWriter - Responsible for writing signal data to a file. Accepts a signal line and a file path and saves the signal data in a specified format.
- TGnuPlotViewer - Visualizes the signal data using GnuPlot. You can configure the file path, axis labels, and graph labels, and execute GnuPlot to render the graph.
