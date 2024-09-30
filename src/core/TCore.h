/**
 * TODO: Add advanced error handling (detailed information in exceptions)
 * TODO: [GLOBAL] Add logging capabilities for signal processing stages
 * TODO: [GLOBAL] Add caching for efficient data reuse
 * TODO: [GLOBAL] Implement unit tests for signal processing methods
 * TODO: [GLOBAL] Add different types of exceptions to handle various error
 * cases
 * TODO: [GLOBAL] ??? Investigate adding asynchronous computation ???
 * TODO: [GLOBAL] ??? Investigate adding interfaces for signal processing ???
 * TODO: [GLOBAL] Validate @throws tags in the documentation
 * ? Consider using "std::optional" for optional parameters ?
 * ? use ++i instead of i++ in for loops ?
 */

#pragma once

#include <stdexcept>

/**
 * @class SignalProcesserException
 * @brief Exception class for signal processing errors.
 *
 * This class is used to handle errors that occur during signal processing.
 * It inherits from `std::runtime_error`, allowing for the inclusion of detailed
 * error messages when an exception is thrown.
 */
class SignalProcesserException : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};