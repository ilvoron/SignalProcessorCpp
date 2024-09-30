/**
 * TODO: Add check if file is not empty before writing.
 */

#pragma once

#include "TPathManager.h"
#include "TSignalLine.h"

#include <string>

/**
 * @struct TFileWriterParams
 * @brief Parameters for writing a signal line to a file.
 */
struct TFileWriterParams {
  const TSignalLine* signalLine =
      nullptr;  ///< Pointer to the signal line to be written.
  std::string filePath =
      PM::DEFAULT_SIGNAL_LINE_FILEPATH;  ///< Path to the file where the signal
                                         ///< line will be saved.
};

/**
 * @class TFileWriter
 * @brief Class responsible for writing a signal line to a file.
 *
 * The TFileWriter class allows saving a signal line to a file at a specified
 * location. It uses the signal line and file path provided either directly or
 * through parameters.
 */
class TFileWriter {
 public:
  /**
   * @brief Constructs a TFileWriter with a signal line and file path.
   *
   * @param signalLine Pointer to the signal line that will be written to the
   * file.
   * @param filePath (optional) Path to the file where the signal line will be
   * saved.
   */
  explicit TFileWriter(const TSignalLine* signalLine,
                       std::string filePath = PM::DEFAULT_SIGNAL_LINE_FILEPATH);

  /**
   * @brief Constructs a TFileWriter using a TFileWriterParams object.
   *
   * @param params A structure containing the parameters, including the signal
   * line and file path.
   */
  explicit TFileWriter(TFileWriterParams params);

  /**
   * @brief Default destructor.
   */
  ~TFileWriter() = default;

  /**
   * @brief Default copy constructor.
   */
  TFileWriter(const TFileWriter&) = default;

  /**
   * @brief Default move constructor.
   */
  TFileWriter(TFileWriter&&) noexcept = default;

  /**
   * @brief Default copy assignment operator.
   */
  TFileWriter& operator=(const TFileWriter&) = default;

  /**
   * @brief Default move assignment operator.
   */
  TFileWriter& operator=(TFileWriter&&) noexcept = default;

  /**
   * @brief Retrieves the parameters used for writing the signal line to a file.
   *
   * @return const TFileWriterParams& A constant reference to the file writer
   * parameters.
   */
  [[nodiscard]] const TFileWriterParams& getParams() const;

  /**
   * @brief Executes the file writing process.
   *
   * This method writes the signal line to the specified file.
   * It should be called after the file writer is properly configured with a
   * signal line and file path.
   */
  void execute() const;

 private:
  TFileWriterParams _params =
      {};  ///< Parameters for writing the signal line to the file.
};