#pragma once
#include "TSignalLine.h"
#include <memory>

/**
 * @brief Parameters for generating a signal line.
 * 
 * This structure contains the default parameters for generating a signal.
 */
struct TGeneratorParams {
	double time = 1.0;            ///< Total time duration of the signal (default: 1.0 second).
	double oscillationFreq = 1.0; ///< Oscillation frequency of the signal (default: 1.0 Hz).
	double initPhase = 0.0;       ///< Initial phase of the signal (default: 0.0 radians).
	double offsetY = 0.0;         ///< Vertical offset of the signal (default: 0.0).
	double amplitude = 1.0;       ///< Amplitude of the signal (default: 1.0).
	double samplingFreq = 100.0;  ///< Sampling frequency of the signal (default: 100.0 Hz).
};

/**
 * @class TGenerator
 * @brief Class for generating a signal line with specified parameters.
 * 
 * This class allows for the generation of a signal line based on configurable
 * parameters and provides access to the generated signal and its parameters.
 */
class TGenerator{
	public:
		/**
		 * @brief Constructs a TGenerator with specified signal parameters.
		 * 
		 * @param time The total time duration of the signal.
		 * @param oscillationFreq The oscillation frequency of the signal.
		 * @param initPhase The initial phase of the signal.
		 * @param offsetY The vertical offset of the signal.
		 * @param amplitude The amplitude of the signal.
		 * @param samplingFreq The sampling frequency of the signal.
		 */
		TGenerator(double time = 1.0,
		           double oscillationFreq = 1.0,
		           double initPhase = 0.0,
		           double offsetY = 0.0,
		           double amplitude = 1.0,
		           double samplingFreq = 100.0);

		/**
		 * @brief Constructs a TGenerator using a TGeneratorParams object.
		 * 
		 * @param params A structure containing the parameters for the signal generation.
		 */
		TGenerator(TGeneratorParams params);

		/**
		 * @brief Destructor for the TGenerator object.
		 * 
		 * Default destructor as no custom resource management is required.
		 */
		~TGenerator() = default;

		/**
		 * @brief Retrieves a pointer to the generated signal line.
		 * 
		 * This method provides access to the signal line generated by the TGenerator.
		 * 
		 * @return const TSignalLine* A pointer to the generated signal line.
		 */
		const TSignalLine* getSignalLine() const;

		/**
		 * @brief Retrieves the parameters used for signal generation.
		 * 
		 * @return const TGeneratorParams& A constant reference to the signal generation parameters.
		 */
		const TGeneratorParams& getParams() const;

		/**
		 * @brief Checks if the signal has been generated.
		 * 
		 * @return bool True if the signal has been generated, false otherwise.
		 */
		bool isExecuted() const;

		/**
		 * @brief Executes the signal generation process.
		 * 
		 * This method generates the signal line based on the current parameters.
		 * Once executed, the signal can be accessed through getSignalLine().
		 */
		void execute();
	private:
		std::unique_ptr<TSignalLine> _sl = nullptr; ///< A unique pointer to the generated signal line.
		TGeneratorParams _params = {};              ///< Parameters for generating the signal line.
		bool _isExecuted = false;                   ///< Flag indicating whether the signal has been generated.
};