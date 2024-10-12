/**
 * @file TCore.hpp
 * @brief Contains the main header file for the SignalProcessorCPP library.
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 *
 * @todo [GLOBAL] Add logging capabilities for signal processing stages
 * @todo [GLOBAL] Add caching for efficient data reuse
 * @todo [GLOBAL] Implement unit tests for signal processing methods
 * @todo [GLOBAL] Add different types of exceptions to handle various error
 * cases
 * @todo [GLOBAL] Investigate adding asynchronous computation
 * @todo [GLOBAL] Investigate adding interfaces for signal processing
 * @todo [GLOBAL] Add module to redefine signal line parameters based on points
 * count and duration/sampling frequency
 * @todo [GLOBAL] Refactor all arguments of constructors and related methods
 * @todo [GLOBAL] Think about adding "chaining" for signal processing methods
 * @todo [GLOBAL] Make unit tests
 */

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;
#endif

constexpr double TWO_PI = 2 * M_PI;

/**
 * @class SignalProcessingError
 * @brief Exception for errors during signal processing.
 * @details This class is used to handle errors that occur during signal
 * processing. It inherits from `std::runtime_error`, which allows for detailed
 * error messages when exceptions are thrown.
 *
 * @todo Add advanced error handling (detailed information in exceptions)
 */
class SignalProcessingError final : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
};