#pragma once
#include "TSignalLine.h"
#include <string>

/**
 * @brief Parameters for writing a signal line to a file.
 */
struct TFileWriterParams {
	const TSignalLine* signalLine = nullptr; ///< Pointer to the signal line to be written.
	const std::string filePath = "";        ///< Path to the file where the signal line will be saved.
};

/**
 * @class TFileWriter
 * @brief Class responsible for writing a signal line to a file.
 * 
 * The TFileWriter class allows saving a signal line to a file at a specified location.
 * It uses the signal line and file path provided either directly or through parameters.
 */
class TFileWriter {
	public:
		/**
		 * @brief Constructs a TFileWriter with a signal line and file path.
		 * 
		 * @param signalLine Pointer to the signal line that will be written to the file.
		 * @param filePath Path to the file where the signal line will be saved.
		 */
		TFileWriter(const TSignalLine* signalLine, const std::string filePath);

		/**
		 * @brief Constructs a TFileWriter using a TFileWriterParams object.
		 * 
		 * @param params A structure containing the parameters, including the signal line and file path.
		 */
		TFileWriter(TFileWriterParams params);

		/**
		 * @brief Default destructor.
		 */
		~TFileWriter() = default;

		/**
		 * @brief Retrieves the parameters used for writing the signal line to a file.
		 * 
		 * @return const TFileWriterParams& A constant reference to the file writer parameters.
		 */
		const TFileWriterParams& getParams() const;

		// TODO: Add check if file not empty
		/**
		 * @brief Executes the file writing process.
		 * 
		 * This method writes the signal line to the specified file.
		 * It should be called after the file writer is properly configured with a signal line and file path.
		 */
		void execute();
	private:
		TFileWriterParams _params = {}; ///< Parameters for writing the signal line to the file.
};