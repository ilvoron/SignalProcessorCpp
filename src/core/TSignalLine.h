#pragma once
#include <vector>
#include <string>

/**
 * @brief Represents a 2D point with x and y coordinates.
 */
struct Point {
	double x; ///< The x-coordinate of the point.
	double y; ///< The y-coordinate of the point.
};

/**
 * @brief Parameters of a signal line.
 * 
 * Contains various parameters used for describing a signal line.
 */
struct TSignalLineParams {
	std::size_t pointsCount;                ///< Number of points in the signal line.
	double time;                            ///< Duration of the signal in seconds.
	double oscillationFreq;                 ///< Oscillation frequency of the signal.
	double initPhase;                       ///< Initial phase of the signal.
	double offsetY;                         ///< Vertical offset of the signal.
	double amplitude;                       ///< Amplitude of the signal.
	double samplingFreq;                    ///< Sampling frequency of the signal.
	bool hasPointsCount;                    ///< Whether the number of points is defined.
	bool hasTime;                           ///< Whether the time duration is defined.
	bool hasOscillationFreq;                ///< Whether the oscillation frequency is defined.
	bool hasInitPhase;                      ///< Whether the initial phase is defined.
	bool hasOffsetY;                        ///< Whether the vertical offset is defined.
	bool hasAmplitude;                      ///< Whether the amplitude is defined.
	bool hasSamplingFreq;                   ///< Whether the sampling frequency is defined.
	std::string xLabel = "Time";            ///< Label for the x-axis (default: "Time").
	std::string yLabel = "Signal Value";    ///< Label for the y-axis (default: "Signal Value").
	std::string graphLabel = "Signal Line"; ///< Label for the graph (default: "Signal Line").
};

/**
 * @class TSignalLine
 * @brief Represents a signal line composed of points with configurable parameters.
 * 
 * This class generates "template" signal line
 * (does not fill the array of points, only allocates memory)
 * and manages a signal line based on input parameters.
 * It allows for setting and retrieving points
 * and provides validation methods to ensure correct operations.
 */
class TSignalLine {
	public:
		/**
		 * @brief Constructs a signal line with the specified parameters.
		 * 
		 * @param time The total time duration of the signal.
		 * @param oscillationFreq The oscillation frequency of the signal.
		 * @param initPhase The initial phase of the signal.
		 * @param offsetY The vertical offset of the signal.
		 * @param amplitude The amplitude of the signal.
		 * @param samplingFreq The sampling frequency of the signal.
		 */
		TSignalLine(double time,
		            double oscillationFreq,
		            double initPhase,
		            double offsetY,
		            double amplitude,
		            double samplingFreq);

		/**
		 * @brief Destructor for the TSignalLine object.
		 * 
		 * Default destructor as no custom resource management is required.
		 */
		~TSignalLine() = default;

		/**
		 * @brief Sets the coordinates of a point in the signal line.
		 * 
		 * This method allows modifying the position of a point at the specified index.
		 * 
		 * @param index The index of the point to be updated.
		 * @param x The new x-coordinate of the point.
		 * @param y The new y-coordinate of the point.
		 */
		void setPoint(unsigned int index, double x, double y);

		/**
		 * @brief Retrieves a point from the signal line by its index.
		 * 
		 * @param index The index of the point to retrieve.
		 * @return const Point& A constant reference to the requested point.
		 * @throws std::out_of_range If the index is out of bounds.
		 */
		const Point& getPoint(unsigned int index) const;

		/**
		 * @brief Retrieves the parameters of the signal line.
		 * 
		 * @return const TSignalLineParams& A constant reference to the signal line parameters.
		 */
		const TSignalLineParams& getParams() const;

	private:
		std::vector<Point> _points;     ///< Container for the points in the signal line.
		TSignalLineParams _params = {}; ///< Parameters that define the signal line.

		/**
		 * @brief Validates that the points have been properly initialized.
		 * 
		 * This method checks whether the signal points are initialized before accessing them.
		 * It throws an exception if the points are not initialized.
		 * 
		 * @throws SignalProcesserException If the points are not initialized.
		 */
		void validatePointsInitialization() const;
};