/**
 * @file TAmplitudeDetector.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TAmplitudeDetector class for detecting
 * the amplitude of a signal.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TSignalLine.hpp"

/**
 * @struct TAmplitudeDetectorParams
 * @brief Contains parameters used for detecting the amplitude of a signal.
 */
struct TAmplitudeDetectorParams {
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to detect the amplitude.
};

/**
 * @class TAmplitudeDetector
 * @brief Class for detecting the amplitude of a signal line using RMS (Root
 * Mean Square).
 */
class TAmplitudeDetector {
   public:
    /**
     * @brief Constructs a TAmplitudeDetector with a signal line.
     *
     * @param signalLine Pointer to the signal line to detect the amplitude.
     */
    explicit TAmplitudeDetector(const TSignalLine* signalLine);

    /**
     * @brief Constructs a TAmplitudeDetector with detection parameters.
     *
     * @param params Structure containing the parameters for amplitude
     * detection.
     */
    explicit TAmplitudeDetector(const TAmplitudeDetectorParams& params);

    /**
     * @brief Default destructor.
     */
    ~TAmplitudeDetector() = default;

    /**
     * @brief Default copy constructor.
     */
    TAmplitudeDetector(const TAmplitudeDetector&) = default;

    /**
     * @brief Default move constructor.
     */
    TAmplitudeDetector(TAmplitudeDetector&&) noexcept = default;

    /**
     * @brief Default copy assignment operator.
     */
    TAmplitudeDetector& operator=(const TAmplitudeDetector&) = default;

    /**
     * @brief Default move assignment operator.
     */
    TAmplitudeDetector& operator=(TAmplitudeDetector&&) noexcept = default;

    /**
     * @brief Retrieves the detected amplitude.
     *
     * @return double Detected amplitude of the signal.
     *
     * @throw SignalProcessingError if the amplitude detection process has not
     * been done.
     */
    [[nodiscard]] double getAmplitude() const;

    /**
     * @brief Retrieves the parameters used for amplitude detection.
     *
     * @return const TAmplitudeDetectorParams& Reference to the detection
     * parameters.
     */
    [[nodiscard]] const TAmplitudeDetectorParams& getParams() const;

    /**
     * @brief Checks whether the amplitude detection has been executed.
     *
     * @return bool True if the amplitude detection process has been executed,
     * false otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the detection of the amplitude of the signal line.
     *
     * @throw SignalProcessingError if the signal line is not specified or does
     * not have duration information.
     */
    void execute();

   private:
    double _amplitude = 0.0;           ///< Detected amplitude of the signal.
    TAmplitudeDetectorParams _params;  ///< Parameters for amplitude detection.
    bool                     _isExecuted =
        false;  ///< Flag indicating whether the detection has been executed.
};