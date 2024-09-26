#pragma once
#include <stdexcept>

/**
 * @brief Macro that throws a SignalProcesserException with a custom message.
 * 
 * This macro simplifies throwing an exception by including the function name
 * where the exception was triggered.
 * 
 * @param message The custom error message to include in the exception.
 */
#define THROW_SIGNAL_PROCESSOR_EXCEPTION(message) throw SignalProcesserException((message), __func__)

/**
 * @class SignalProcesserException
 * @brief Exception class for signal processing errors.
 * 
 * Inherits from std::runtime_error and is designed to provide enhanced error
 * messages that include the function name where the exception occurred.
 */
class SignalProcesserException : public std::runtime_error {
	public:
		/**
		 * @brief Constructs a SignalProcesserException with a message and function name.
		 * 
		 * @param message The custom error message to include in the exception.
		 * @param func The name of the function where the exception occurred.
		 */
		explicit SignalProcesserException(const std::string& message, const char* func)
			: std::runtime_error(FormatMessage(message, func)) {}

		/**
		 * @brief Destructor for the SignalProcesserException object.
		 * 
		 * Default destructor as no custom resource management is required.
		 */
		~SignalProcesserException() = default;

	private:
		/**
		 * @brief Formats the error message to include the function name.
		 * 
		 * This static method combines the error message and the function name
		 * into a single formatted string.
		 * 
		 * @param message The custom error message.
		 * @param func The name of the function where the exception occurred.
		 * @return std::string The formatted error message.
		 */
		static std::string FormatMessage(const std::string& message, const char* func) {
			return message + " | Function: " + func;
		}
};