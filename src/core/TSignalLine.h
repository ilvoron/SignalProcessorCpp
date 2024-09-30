/**
 * TODO: Add method to equalize signal lines
 * TODO: ??? Add methods-aliases for signal line processing ???
 *       ??? Or create a new module (class) such as "TSignalOperations" ???
 *       ??? or overload "+", "-" and other operators ???
 *       ??? or all together ???
 * TODO: ??? Add generation inside the signal line ???
 * !TODO: ??? Make a class for Point ???
 * TODO: Add push/pop point method
 * !TODO: Make it get only x or y coordinates vector
 * !TODO: void setPoint(std::size_t index, const Point& point);
 * TODO: Add constuctor for just points count
 * TODO: Add set params method
 */

#pragma once

#include <string>
#include <vector>

/**
 * @namespace SL
 * @brief Contains default parameters used for describing a signal line.
 */
namespace SL {

static constexpr double DEFAULT_INACCURACY =
    0.05;  ///< Default tolerance for inaccuracy in comparisons.
static constexpr double DEFAULT_TIME =
    1.0;  ///< Default duration of the signal in seconds.
static constexpr double DEFAULT_OSCILLATION_FREQ =
    1.0;  ///< Default oscillation frequency of the signal.
static constexpr double DEFAULT_INIT_PHASE =
    0.0;  ///< Default initial phase of the signal.
static constexpr double DEFAULT_OFFSET_Y =
    0.0;  ///< Default vertical offset of the signal.
static constexpr double DEFAULT_AMPLITUDE =
    1.0;  ///< Default amplitude of the signal.
static constexpr double DEFAULT_SAMPLING_FREQ =
    100.0;  ///< Default sampling frequency of the signal.
static constexpr double DEFAULT_NORMALIZE_FACTOR =
    1.0;  ///< Default normalization factor for the signal.
static const std::string DEFAULT_X_LABEL =
    "X Axis";  ///< Default label for the x-axis.
static const std::string DEFAULT_Y_LABEL =
    "Y Axis";  ///< Default label for the y-axis.
static const std::string DEFAULT_GRAPH_LABEL =
    "Graph";  ///< Default label for the graph.

}  // namespace SL

/**
 * @struct Point
 * @brief Represents a 2D point with x and y coordinates.
 */
struct Point {
  double x = 0.0;  ///< The x-coordinate of the point.
  double y = 0.0;  ///< The y-coordinate of the point.
};

/**
 * @struct TSignalLineParams
 * @brief Contains parameters used for describing a signal line.
 */
struct TSignalLineParams {
  std::size_t pointsCount = 0;   ///< Total number of points in the signal line.
  double time = 0.0;             ///< Duration in seconds.
  double oscillationFreq = 0.0;  ///< Oscillation frequency.
  double initPhase = 0.0;        ///< Initial phase.
  double offsetY = 0.0;          ///< Vertical offset.
  double amplitude = 0.0;        ///< Amplitude.
  double samplingFreq = 0.0;     ///< Sampling frequency.
  double normalizeFactor = 0.0;  ///< Normalization factor.
  mutable double maxValue = 0.0;  ///< Maximum value of the signal.
  mutable double minValue = 0.0;  ///< Minimum value of the signal.
  bool hasPointsCount =
      false;             ///< Indicates if the number of points is specified.
  bool hasTime = false;  ///< Indicates if the signal duration is specified.
  bool hasOscillationFreq = false;  ///< Indicates if the oscillation frequency
                                    ///< is specified.
  bool hasInitPhase = false;  ///< Indicates if the initial phase is specified.
  bool hasOffsetY = false;  ///< Indicates if the vertical offset is specified.
  bool hasAmplitude = false;  ///< Indicates if the amplitude is specified.
  bool hasSamplingFreq =
      false;  ///< Indicates if the sampling frequency is specified.
  bool hasNormalizeFactor = false;   ///< Indicates if the normalization factor
                                     ///< is specified.
  mutable bool hasMaxValue = false;  ///< Indicates if the maximum value is
                                     ///< specified.
  mutable bool hasMinValue = false;  ///< Indicates if the minimum value is
  std::string xLabel =
      SL::DEFAULT_X_LABEL;  ///< (optional) Label for the x-axis.
  std::string yLabel =
      SL::DEFAULT_Y_LABEL;  ///< (optional) Label for the y-axis.
  std::string graphLabel =
      SL::DEFAULT_GRAPH_LABEL;  ///< (optional) Label for the graph.
};

/**
 * @class TSignalLine
 * @brief Represents a signal line composed of points with various configurable
 * parameters.
 *
 * TSignalLine is responsible for managing a signal line by allocating memory
 * for points and adjusting signal parameters. It provides methods to set and
 * retrieve points and to validate the correctness of the signal's parameters.
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
   * @param normalizeFactor (optional) Normalization factor for the signal.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   */
  explicit TSignalLine(double time,
                       double oscillationFreq,
                       double initPhase,
                       double offsetY,
                       double amplitude,
                       double samplingFreq,
                       double normalizeFactor,
                       std::string xLabel = SL::DEFAULT_X_LABEL,
                       std::string yLabel = SL::DEFAULT_Y_LABEL,
                       std::string graphLabel = SL::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a signal line based on the number of points.
   *
   * @param pointsCount Number of points in the signal line.
   * @param xLabel (optional) Label for the x-axis.
   * @param yLabel (optional) Label for the y-axis.
   * @param graphLabel (optional) Label for the graph.
   */
  explicit TSignalLine(std::size_t pointsCount,
                       std::string xLabel = SL::DEFAULT_X_LABEL,
                       std::string yLabel = SL::DEFAULT_Y_LABEL,
                       std::string graphLabel = SL::DEFAULT_GRAPH_LABEL);

  /**
   * @brief Constructs a signal line based on the given parameters.
   *
   * This constructor attempts to form a signal using either the time or
   * sampling frequency (ignoring other parameters if necessary). If the signal
   * can be formed this way, all points are initialized with zero values.
   *
   * If neither time nor sampling frequency can be used to form the signal,
   * the signal will be created based solely on the number of points, if
   * available.
   *
   * @param params A structure containing parameters for configuring the signal
   * line.
   */
  explicit TSignalLine(TSignalLineParams params);

  explicit TSignalLine(const TSignalLine* signalLine,
                       double offsetX = 0.0,
                       double offsetY = 0.0);

  /**
   * @brief Default destructor.
   */
  ~TSignalLine() = default;

  /**
   * @brief Default copy constructor.
   */
  TSignalLine(const TSignalLine&) = default;

  /**
   * @brief Default move constructor.
   */
  TSignalLine(TSignalLine&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TSignalLine& operator=(const TSignalLine&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TSignalLine& operator=(TSignalLine&&) noexcept = default;

  /**
   * @brief Sets the coordinates of a specific point in the signal line.
   *
   * @param index Index of the point to be updated.
   * @param xCoord The new x-coordinate of the point.
   * @param yCoord The new y-coordinate of the point.
   */
  void setPoint(std::size_t index, double xCoord, double yCoord);

  /**
   * @brief Retrieves a point from the signal line by its index.
   *
   * @param index Index of the point to retrieve.
   * @return const Point& A constant reference to the requested point.
   * @throws std::out_of_range If the index is out of bounds.
   */
  [[nodiscard]] const Point& getPoint(std::size_t index) const;

  /**
   * @brief Retrieves the parameters of the signal line.
   *
   * @return const TSignalLineParams& A constant reference to the signal line
   * parameters.
   */
  [[nodiscard]] const TSignalLineParams& getParams() const;

  /**
   * @brief Compares this signal line with another for approximate equality.
   *
   * @param signalLine Pointer to the signal line to compare with.
   * @param inaccuracy Allowed inaccuracy for the comparison.
   * @return true If the two signal lines are approximately equal.
   * @return false Otherwise.
   */
  [[nodiscard]] bool equals(const TSignalLine* signalLine,
                            double inaccuracy = SL::DEFAULT_INACCURACY) const;

  /**
   * @brief Determines whether the signal can be formed based on time and/or
   * sampling frequency rather than the number of points.
   *
   * This method checks if the signal line can be generated using parameters
   * such as time or sampling frequency instead of relying on the number of
   * points.
   *
   * @return true If the signal can be formed based on time or sampling
   * frequency.
   * @return false Otherwise.
   */
  [[nodiscard]] bool canFormFromTimeOrFrequency() const;

  /**
   * @brief Finds the maximum value in the signal line.
   *
   * This method iterates through all points in the signal line to find the
   * maximum value. If the maximum value has already been found and is stored
   * in the parameters, the stored value is returned instead.
   *
   * @param forceUpdate (optional) Forces the method to recalculate the maximum
   * value.
   */
  [[nodiscard]] double findMax(bool forceUpdate = false) const;

  /**
   * @brief Finds the minimum value in the signal line.
   *
   * This method iterates through all points in the signal line to find the
   * minimum value. If the minimum value has already been found and is stored
   * in the parameters, the stored value is returned instead.
   *
   * @param forceUpdate (optional) Forces the method to recalculate the minimum
   * value.
   */
  [[nodiscard]] double findMin(bool forceUpdate = false) const;

  /**
   * @brief Checks whether two points are approximately equal in the
   * x-coordinate.
   *
   * @param point1 First point for comparison.
   * @param point2 Second point for comparison.
   * @param inaccuracy Allowed inaccuracy for the x-coordinate.
   * @return true If the points are approximately equal in the x-coordinate.
   * @return false Otherwise.
   */
  [[nodiscard]] static bool areCloseX(
      const Point& point1,
      const Point& point2,
      double inaccuracy = SL::DEFAULT_INACCURACY);

  /**
   * @brief Checks whether two points are approximately equal in the
   * y-coordinate.
   *
   * @param point1 First point for comparison.
   * @param point2 Second point for comparison.
   * @param inaccuracy Allowed inaccuracy for the y-coordinate.
   * @return true If the points are approximately equal in the y-coordinate.
   * @return false Otherwise.
   */
  [[nodiscard]] static bool areCloseY(
      const Point& point1,
      const Point& point2,
      double inaccuracy = SL::DEFAULT_INACCURACY);

  /**
   * @brief Checks whether two points are approximately equal.
   *
   * @param point1 First point for comparison.
   * @param point2 Second point for comparison.
   * @param inaccuracy Allowed inaccuracy for the x and y coordinates.
   * @return true If the points are approximately equal.
   * @return false Otherwise.
   */
  [[nodiscard]] static bool areClose(
      const Point& point1,
      const Point& point2,
      double inaccuracy = SL::DEFAULT_INACCURACY);

 private:
  std::vector<Point> _points;  ///< Container for the points in the signal line.
  TSignalLineParams _params = {};  ///< Parameters of the signal line.

  /**
   * @brief Validates that the points have been properly initialized.
   *
   * This method checks whether the signal points are initialized before
   * accessing them. It throws an exception if the points are not initialized.
   *
   * @throws SignalProcesserException If the points are not initialized.
   */
  void validatePointsInitialization() const;
};