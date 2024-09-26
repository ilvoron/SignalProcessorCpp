#pragma once
#include <vector>
#include <string>

// TODO: Add method to equalize signal lines
// TODO: Add cloning method for signal lines
// TODO: ??? Add methods-aliases for signal line processing ???
//       ??? Or create a new module (class) such as "TSignalOperations" ???
//       ??? or overload "+", "-" and other operators ???
//       ??? or all together ???
//       ??? or what ???
// TODO: ??? Add generation inside the signal line ???

/**
 * @brief Represents a 2D point with x and y coordinates.
 */
struct Point {
	double x; ///< The x-coordinate of the point.
	double y; ///< The y-coordinate of the point.
};

/**
 * @brief Contains various parameters used for describing a signal line.
 */
struct TSignalLineParams {
	std::size_t pointsCount;          ///< Total number of points in the signal line.
	double time;                      ///< Duration of the signal in seconds.
	double oscillationFreq;           ///< Oscillation frequency of the signal.
	double initPhase;                 ///< Initial phase of the signal.
	double offsetY;                   ///< Vertical offset of the signal.
	double amplitude;                 ///< Amplitude of the signal.
	double samplingFreq;              ///< Sampling frequency of the signal.
	bool hasPointsCount;              ///< Indicates if the number of points is specified.
	bool hasTime;                     ///< Indicates if the signal duration is specified.
	bool hasOscillationFreq;          ///< Indicates if the oscillation frequency is specified.
	bool hasInitPhase;                ///< Indicates if the initial phase is specified.
	bool hasOffsetY;                  ///< Indicates if the vertical offset is specified.
	bool hasAmplitude;                ///< Indicates if the amplitude is specified.
	bool hasSamplingFreq;             ///< Indicates if the sampling frequency is specified.
	std::string xLabel = "X Axis";    ///< Label for the x-axis (default: "X Axis").
	std::string yLabel = "Y Axis";    ///< Label for the y-axis (default: "Y Axis").
	std::string graphLabel = "Graph"; ///< Label for the graph (default: "Graph").
};

/**
 * @class TSignalLine
 * @brief Represents a signal line composed of points with various configurable parameters.
 * 
 * TSignalLine is responsible for managing a signal line
 * by allocating memory for points and adjusting signal parameters.
 * It provides methods to set and retrieve points and
 * to validate the correctness of the signal's parameters.
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
		 * @param xLabel Label for the x-axis (optional, default: "X Axis").
		 * @param yLabel Label for the y-axis (optional, default: "Y Axis").
		 * @param graphLabel Label for the graph (optional, default: "Graph").
		 */
		TSignalLine(double time,
		            double oscillationFreq,
		            double initPhase,
		            double offsetY,
		            double amplitude,
		            double samplingFreq,
		            std::string xLabel = "X Axis",
		            std::string yLabel = "Y Axis",
		            std::string graphLabel = "Graph");

		/**
		 * @brief Constructs a signal line based on the number of points.
		 * 
		 * @param pointsCount Number of points in the signal line.
		 * @param xLabel Label for the x-axis (optional, default: "X Axis").
		 * @param yLabel Label for the y-axis (optional, default: "Y Axis").
		 * @param graphLabel Label for the graph (optional, default: "Graph").
		 */
		TSignalLine(std::size_t pointsCount,
		            std::string xLabel = "X Axis",
		            std::string yLabel = "Y Axis",
		            std::string graphLabel = "Graph");

		/**
		 * @brief Default destructor.
		 */
		~TSignalLine() = default;

		/**
		 * @brief Sets the coordinates of a specific point in the signal line.
		 * 
		 * @param index Index of the point to be updated.
		 * @param x The new x-coordinate of the point.
		 * @param y The new y-coordinate of the point.
		 */
		void setPoint(std::size_t index, double x, double y);

		/**
		 * @brief Retrieves a point from the signal line by its index.
		 * 
		 * @param index Index of the point to retrieve.
		 * @return const Point& A constant reference to the requested point.
		 * @throws std::out_of_range If the index is out of bounds.
		 */
		const Point& getPoint(std::size_t index) const;

		/**
		 * @brief Retrieves the parameters of the signal line.
		 * 
		 * @return const TSignalLineParams& A constant reference to the signal line parameters.
		 */
		const TSignalLineParams& getParams() const;

		/**
		 * @brief Compares this signal line with another for approximate equality.
		 * 
		 * @param signalLine Pointer to the signal line to compare with.
		 * @param inaccuracy Allowed inaccuracy for the comparison (default is 0.05).
		 * @return true If the two signal lines are approximately equal.
		 * @return false Otherwise.
		 */
		bool equals(const TSignalLine* signalLine, double inaccuracy = 0.05) const;

	private:
		std::vector<Point> _points;     ///< Container for the points in the signal line.
		TSignalLineParams _params = {}; ///< Parameters of the signal line.

		/**
		 * @brief Checks whether two points are approximately equal in the x-coordinate.
		 * 
		 * @param point1 First point for comparison.
		 * @param point2 Second point for comparison.
		 * @param inaccuracy Allowed inaccuracy for the x-coordinate (default is 0.05).
		 * @return true If the points are approximately equal in the x-coordinate.
		 * @return false Otherwise.
		 */
		bool areCloseX(const Point& point1, const Point& point2, double inaccuracy = 0.05) const;

		/**
		 * @brief Checks whether two points are approximately equal in the y-coordinate.
		 * 
		 * @param point1 First point for comparison.
		 * @param point2 Second point for comparison.
		 * @param inaccuracy Allowed inaccuracy for the x-coordinate (default is 0.05).
		 * @return true If the points are approximately equal in the y-coordinate.
		 * @return false Otherwise.
		 */
		bool areCloseY(const Point& point1, const Point& point2, double inaccuracy = 0.05) const;

		/**
		 * @brief Checks whether two points are approximately equal
		 * 
		 * @param point1 First point for comparison.
		 * @param point2 Second point for comparison.
		 * @param inaccuracy Allowed inaccuracy for the x-coordinate (default is 0.05).
		 * @return true If the points are approximately equal.
		 * @return false Otherwise.
		 */
		bool areClose(const Point& point1, const Point& point2, double inaccuracy = 0.05) const;

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