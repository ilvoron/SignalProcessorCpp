/**
 * @file TSignalLine.hpp
 * @brief Declares the TSignalLine class for representing discrete signal lines,
 * along with supporting structures and constants for signal processing.
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

/**
 * @namespace SL
 * @brief Contains default parameter values used in signal generation and
 * processing.
 */
namespace SL {

    /**
     * @enum Preference
     * @brief Specifies the preference for signal line creation.
     * @details This enumeration defines two preferences for creating signal
     * lines:
     *
     * - `Auto`: This preference automatically determines the best approach
     *
     * - `PreferPointsCount`: This preference prioritizes the total number of
     *   points in the signal line. When creating a signal line, the number of
     *   points is specified, and the duration and frequency remain unaffected.
     *
     * - `PreferDurationAndSamplingFreq`: This preference prioritizes the
     * duration and frequency of the signal line. When creating a signal line,
     * the duration and frequency are specified, and the total number of points
     * is calculated based on the provided duration and frequency.
     */
    enum class Preference : std::uint8_t {
        Auto,  ///< Automatically determine the preference based on the provided
               ///< parameters.
        PreferPointsCount,  ///< Prefer points count when creating a signal
                            ///< line.
        PreferDurationAndSamplingFreq  ///< Prefer duration and sampling
                                       ///< frequency when creating a signal
                                       ///< line.
    };

    // Signal parameters
    static constexpr double DEFAULT_SAMPLING_FREQ_HZ =
        100.0;  ///< Default sampling frequency of the signal, in Hertz.
    static constexpr double DEFAULT_DURATION_SECONDS =
        1.0;  ///< Default duration in seconds for the signal's duration.
    static constexpr double DEFAULT_FREQ_HZ =
        1.0;  ///< Default oscillation frequency of the signal, in Hertz.
    static constexpr double DEFAULT_INIT_PHASE =
        0.0;  ///< Default initial phase of the signal, in radians.
    static constexpr double DEFAULT_OFFSET_Y =
        0.0;  ///< Default vertical offset applied to the signal.
    static constexpr double DEFAULT_AMPLITUDE =
        1.0;  ///< Default amplitude of the signal.

    // Graphical parameters
    static const std::string DEFAULT_X_LABEL =
        "X Axis";  ///< Default label for the x-axis, usually representing time.
    static const std::string DEFAULT_Y_LABEL =
        "Y Axis";  ///< Default label for the y-axis, usually representing
                   ///< amplitude.
    static const std::string DEFAULT_GRAPH_LABEL =
        "Graph";  ///< Default label for the graph title.

    // Other parameters
    static constexpr double DEFAULT_INACCURACY =
        1e-9;  ///< Default tolerance for floating-point comparisons.
    static constexpr double DEFAULT_NORMALIZE_FACTOR =
        1.0;  ///< Default normalization factor applied to signals. See @ref
              ///< TSignalLineParams::normalizeFactor "normalizeFactor" in
              ///< TSignalLineParams for more information.
    static constexpr auto DEFAULT_PREFERENCE =
        Preference::Auto;  ///< Default preference for signal line creation.

}  // namespace SL

/**
 * @struct Point
 * @brief Represents a 2D point with x and y coordinates.
 *
 * @todo Consider converting in the future if additional functionality, such as
 * operations on points (e.g., addition, distance calculation), or encapsulation
 * of data is required. --> add getPoints() and setPoints() methods in the
 * TSignalLine class.
 */
struct Point {
    double x = 0.0;  ///< The x-coordinate of the point (horizontal position).
    double y = 0.0;  ///< The y-coordinate of the point (vertical position).
};

/**
 * @struct TSignalLineParams
 * @brief Contains parameters that describe a signal line in 2D space.
 *
 * @note Some parameters are optional and represented by std::optional. These
 * can be set by the user or remain unset, in which case default values or
 * behaviors are applied.
 */
struct TSignalLineParams {
    // Signal parameters
    std::optional<double> samplingFrequency =
        SL::DEFAULT_SAMPLING_FREQ_HZ;  ///< Sampling frequency of the signal, in
                                       ///< Hertz.
    std::optional<double> duration =
        SL::DEFAULT_DURATION_SECONDS;  ///< Duration of the signal in seconds.
    std::optional<double> oscillationFrequency =
        SL::DEFAULT_FREQ_HZ;  ///< Oscillation frequency of the signal,
                              ///< in Hertz.
    std::optional<double> initPhase =
        SL::DEFAULT_INIT_PHASE;  ///< Initial phase of the signal, in radians.
    std::optional<double> offsetY =
        SL::DEFAULT_OFFSET_Y;  ///< Vertical offset of the signal.
    std::optional<double> amplitude =
        SL::DEFAULT_AMPLITUDE;  ///< Amplitude of the signal.

    // Graphical parameters
    std::optional<std::string> xLabel =
        SL::DEFAULT_X_LABEL;  ///< Label for the x-axis.
    std::optional<std::string> yLabel =
        SL::DEFAULT_Y_LABEL;  ///< Label for the y-axis.
    std::optional<std::string> graphLabel =
        SL::DEFAULT_GRAPH_LABEL;  ///< Label for the graph.

    // Other parameters
    std::size_t pointsCount =
        0;  ///< Total number of points in the signal line.
    std::optional<double> normalizeFactor =
        SL::DEFAULT_NORMALIZE_FACTOR;  ///< Normalization factor for the signal,
                                       ///< crucial for modules like
                                       ///< TDifferentiator. It accounts for the
                                       ///< transformation from time domain to
                                       ///< frequency domain, particularly in
                                       ///< derivative operations. The factor
                                       ///< includes a division by 2pi, ensuring
                                       ///< correct scaling for periodic signals
                                       ///< described using angular frequencies
                                       ///< (radians per second).
    mutable std::optional<double> maxValue =
        std::nullopt;  ///< Cached maximum value of the signal. Use findMax to
                       ///< compute.
    mutable std::optional<double> minValue =
        std::nullopt;  ///< Cached minimum value of the signal. Use findMin to
                       ///< compute.
};

/**
 * @class TSignalLine
 * @brief Represents a discrete signal formed by a series of points.
 *
 * @todo Add functionality to retrieve x or y coordinate vectors for easier data
 * extraction.
 * @todo Consider a method to set parameters dynamically after object creation.
 * @todo Implement methods for adding or removing points (push/pop).
 * @todo Add a method for equalizing signal lines for comparison or adjustment.
 * @todo Explore adding methods-aliases for signal processing (e.g., overloaded
 * operators for addition/subtraction).
 * @todo Investigate adding a dedicated module/class for complex signal
 * operations.
 * @todo Consider built-in signal generation methods inside the class.
 * @todo Consider about transforming the class into an interface for different
 * signal types, such as sine wave or tan wave or other.
 */
class TSignalLine {
   public:
    /**
     * @brief Constructs a signal line with specified parameters based on
     * duration and sampling frequency
     *
     * @param samplingFrequency Sampling frequency in Hertz (must be
     * positive).
     * @param duration Duration of the signal in seconds (must be
     * positive).
     * @param oscillationFrequency Oscillation frequency in Hertz (cycles per
     * second).
     * @param initPhase Initial phase in radians (shifts the signal along the
     * time axis).
     * @param offsetY Vertical offset applied to the signal (shifts vertically).
     * @param amplitude Amplitude representing the peak value.
     * @param normalizeFactor Normalization factor for adjusting
     * amplitude.
     * @param xLabel Label for the x-axis (defaults to
     * SL::DEFAULT_X_LABEL).
     * @param yLabel Label for the y-axis (defaults to
     * SL::DEFAULT_Y_LABEL).
     * @param graphLabel Label for the graph's title (defaults to
     * SL::DEFAULT_GRAPH_LABEL).
     *
     * @throws SignalProcessingError If `duration` or `samplingFreq` are
     * not positive.
     * @note This constructor allocates memory for the signal points (0.0 for
     * both coordinates) but does not generate a waveform.
     */
    explicit TSignalLine(
        double                samplingFrequency = SL::DEFAULT_SAMPLING_FREQ_HZ,
        double                duration          = SL::DEFAULT_DURATION_SECONDS,
        std::optional<double> oscillationFrequency = SL::DEFAULT_FREQ_HZ,
        std::optional<double> initPhase            = SL::DEFAULT_INIT_PHASE,
        std::optional<double> offsetY              = SL::DEFAULT_OFFSET_Y,
        std::optional<double> amplitude            = SL::DEFAULT_AMPLITUDE,
        std::optional<double> normalizeFactor = SL::DEFAULT_NORMALIZE_FACTOR,
        std::optional<std::string> xLabel     = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel     = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = SL::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a signal line with a specific number of points.
     *
     * @param pointsCount Number of points in the signal line (initialized to
     * (0.0, 0.0)).
     * @param xLabel Label for the x-axis (defaults to
     * SL::DEFAULT_X_LABEL).
     * @param yLabel Label for the y-axis (defaults to
     * SL::DEFAULT_Y_LABEL).
     * @param graphLabel Label for the graph's title (defaults to
     * SL::DEFAULT_GRAPH_LABEL).
     *
     * @note This constructor allocates memory for the signal points (0.0 for
     * both coordinates) but does not generate a waveform.
     */
    explicit TSignalLine(
        std::size_t                pointsCount,
        std::optional<std::string> xLabel     = SL::DEFAULT_X_LABEL,
        std::optional<std::string> yLabel     = SL::DEFAULT_Y_LABEL,
        std::optional<std::string> graphLabel = SL::DEFAULT_GRAPH_LABEL);

    /**
     * @brief Constructs a signal line using provided parameters.
     * @details Attempts to form a signal based on the provided parameters. For
     * `Auto` preference, if both `duration` and `samplingFreq` are
     * available, the signal is formed accordingly, and the total number of
     * points is calculated. All points are initialized with default values (0.0
     * for both x and y). If only `pointsCount` is provided, the signal is
     * created with that many points.
     *
     * @param params Parameters for the signal line, including optional values
     * like duration, frequency, and number of points.
     * @param preference Preference for signal line creation (defaults to Auto).
     *
     * @throws SignalProcessingError If `duration` or `samplingFreq` are
     * not positive; `duration` & `oscillationFreq` neither `pointsCount`
     * are set.
     * @note This constructor initializes the signal line's points with default
     * values and does not generate a specific signal (e.g., sine wave). If
     * additional parameters like labels or normalization factors are included
     * in `params`, they will be preserved for future processing.
     */
    explicit TSignalLine(
        TSignalLineParams             params,
        std::optional<SL::Preference> preference = SL::DEFAULT_PREFERENCE);

    /**
     * @brief Copy constructor to create a new signal line from an existing one
     * with offsets.
     * @details Creates a copy of an existing signal line, applying horizontal
     * (`offsetX`) and vertical (`offsetY`) offsets to each point. The copied
     * signal retains all original parameters (e.g., amplitude, frequency) but
     * adjusts coordinates based on the specified offsets.
     *
     * @param signalLine Pointer to the original signal line (must be valid and
     * have a defined number of points).
     * @param offsetX Horizontal offset for x-coordinates of all points
     * (defaults to 0.0).
     * @param offsetY Vertical offset for y-coordinates of all points (defaults
     * to 0.0).
     *
     * @throws SignalProcessingError If the signal line pointer is null or if
     * the number of points is invalid (e.g., zero).
     * @note This constructor adjusts only the points' positions and does not
     * alter other parameters of the signal.
     */
    explicit TSignalLine(const TSignalLine* signalLine,
                         double             offsetX = 0.0,
                         double             offsetY = 0.0);

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
     * @brief Sets the coordinates of a point in the signal line.
     *
     * @param index The index of the point to set (must be within range).
     * @param xCoord The new x-coordinate.
     * @param yCoord The new y-coordinate.
     *
     * @throws std::out_of_range If the index is out of bounds (checked
     * using `std::vector::at()`).
     * @note Coordinates at the specified index are completely replaced by
     * the new values.
     */
    void setPoint(std::size_t index, double xCoord, double yCoord);

    /**
     * @brief Sets the coordinates of a point in the signal line.
     *
     * @param index The index of the point to set (must be within range).
     * @param point The new point to set.
     *
     * @throws std::out_of_range If the index is out of bounds (checked using
     * `std::vector::at()`).
     * @note Coordinates at the specified index are completely replaced by the
     * new values.
     */
    void setPoint(std::size_t index, Point point);

    /**
     * @brief Retrieves a point by its index.
     *
     * @param index The index of the point to retrieve (must be within bounds).
     * @return const Point& A constant reference to the point at the specified
     * index.
     *
     * @throws std::out_of_range If the index is out of bounds (checked using
     * `std::vector::at()`).
     */
    [[nodiscard]] const Point& getPoint(std::size_t index) const;

    /**
     * @brief Retrieves the parameters of the signal line.
     *
     * @return const TSignalLineParams& A constant reference providing read-only
     * access to the parameters.
     */
    [[nodiscard]] const TSignalLineParams& getParams() const;

    /**
     * @brief Compares two signal lines for approximate equality.
     * @details Checks if the two signal lines are approximately equal by
     * comparing their points within a specified tolerance (`inaccuracy`),
     * focusing on the first and last points for quick similarity determination.
     *
     * @param signalLine Pointer to the other signal line (must be valid and
     * have defined points).
     * @param inaccuracy Tolerance for comparison (higher value
     * allows greater deviation).
     * @return true If the signal lines are approximately equal within the
     * specified inaccuracy; false otherwise.
     *
     * @throws SignalProcessingError If `signalLine` is null, points count is
     * not initialized, or if `inaccuracy` is negative.
     * @note The method compares only the first and last points for efficiency.
     * For precise comparisons, additional methods can be used.
     */
    [[nodiscard]] bool equals(
        const TSignalLine*    signalLine,
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY) const;

    /**
     * @brief Finds the maximum value in the signal line.
     * @details Iterates through all points to find the maximum y-coordinate. If
     * the maximum value is cached, it is returned unless `forceUpdate` is true,
     * in which case the value is recalculated.
     *
     * @param forceUpdate If true, forces recalculation of the
     * maximum value.
     * @return double The maximum y-coordinate value in the signal line.
     */
    [[nodiscard]] double findMax(bool forceUpdate = false) const;

    /**
     * @brief Finds the minimum value in the signal line.
     * @details Iterates through all points to find the minimum y-coordinate. If
     * the minimum value is cached, it is returned unless `forceUpdate` is true,
     * in which case the value is recalculated.
     *
     * @param forceUpdate If true, forces recalculation of the
     * minimum value.
     * @return double The minimum y-coordinate value in the signal line.
     */
    [[nodiscard]] double findMin(bool forceUpdate = false) const;

    /**
     * @brief Removes the DC component from the signal line.
     */
    void removeDCComponent(
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY);

    /**
     * @brief Checks whether two points are approximately equal in the
     * x-coordinate.
     * @details Compares the x-coordinates of two points to determine
     * approximate equality within a specified inaccuracy, accounting for
     * floating-point precision issues.
     *
     * @param point1 The first point to compare.
     * @param point2 The second point to compare.
     * @param inaccuracy Allowed inaccuracy for comparison (default:
     * SL::DEFAULT_INACCURACY).
     * @return true If the x-coordinates are approximately equal; false
     * otherwise.
     *
     * @throw SignalProcessingError If the inaccuracy is negative.
     * @todo Move this method to the `Point` class if created.
     */
    [[nodiscard]] static bool areCloseX(
        const Point&          point1,
        const Point&          point2,
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY);

    /**
     * @brief Checks whether two points are approximately equal in the
     * y-coordinate.
     * @details Compares the y-coordinates of two points for approximate
     * equality within a specified inaccuracy, addressing floating-point
     * precision issues.
     *
     * @param point1 The first point to compare.
     * @param point2 The second point to compare.
     * @param inaccuracy Allowed inaccuracy for comparison (default:
     * SL::DEFAULT_INACCURACY).
     * @return true If the y-coordinates are approximately equal; false
     * otherwise.
     *
     * @throw SignalProcessingError If the inaccuracy is negative.
     * @todo Move this method to the `Point` class if created.
     */
    [[nodiscard]] static bool areCloseY(
        const Point&          point1,
        const Point&          point2,
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY);

    /**
     * @brief Checks whether two points are approximately equal in both x and y
     * coordinates.
     * @details Compares both coordinates of two points to determine approximate
     * equality within a specified inaccuracy. If either coordinate exceeds the
     * tolerance, the points are considered unequal.
     *
     * @param point1 The first point to compare.
     * @param point2 The second point to compare.
     * @param inaccuracy Allowed inaccuracy for both coordinates.
     * @return true If both coordinates are approximately equal; false
     * otherwise.
     *
     * @todo Move this method to the `Point` class if created.
     */
    [[nodiscard]] static bool areClose(
        const Point&          point1,
        const Point&          point2,
        std::optional<double> inaccuracy = SL::DEFAULT_INACCURACY);

   private:
    std::vector<Point>
        _points;  ///< Points of the signal line (x, y coordinates).
    TSignalLineParams _params =
        {};  ///< Parameters defining the signal line
             ///< (e.g., duration, frequency, amplitude).

    /**
     * @brief Finds a value in the signal based on a custom comparison function.
     * @details Iterates through all points, comparing their y-values using the
     * provided comparison function (e.g., `greater-than` for maximum,
     * `less-than` for minimum). The result is cached for performance. If
     * `forceUpdate` is true, the method recalculates the value, ignoring the
     * cache.
     *
     * @param cachedValue A reference to the cached result. If valid and
     * `forceUpdate` is false, the cached value is returned.
     * @param comparator A function defining the condition for selecting a value
     * (accepts two `double` arguments and returns a boolean).
     * @param forceUpdate If true, forces recalculation even if the
     * value is cached.
     * @return double The value satisfying the comparison function, either from
     * cache or recalculated.
     */
    [[nodiscard]] double findByComparison(
        std::optional<double>&                     cachedValue,
        const std::function<bool(double, double)>& comparator,
        bool                                       forceUpdate = false) const;
};