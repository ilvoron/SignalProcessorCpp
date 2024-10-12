/**
 * @file TFileWriter.hpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the declaration of the TFileWriter class, responsible for
 * writing signal lines to files.
 * @version 2.1.0.0
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#pragma once

#include "TPathManager.hpp"
#include "TSignalLine.hpp"

#include <string>

/**
 * @namespace FM
 * @brief Contains default flags and configurations for file management.
 */
namespace FM {

    static constexpr bool DEFAULT_REWRITE_ENABLED =
        true;  ///< Default flag indicating whether the file should be
               ///< overwritten if it already exists.

}  // namespace FM

/**
 * @struct TFileWriterParams
 * @brief Parameters for writing a signal line to a file.
 */
struct TFileWriterParams {
    const TSignalLine* signalLine =
        nullptr;  ///< Pointer to the signal line to be written.
    std::string filePath =
        PM::DEFAULT_SIGNAL_LINE_FILEPATH;  ///< Path to the file where the
                                           ///< signal line will be saved.
    bool isRewriteEnabled =
        FM::DEFAULT_REWRITE_ENABLED;  ///< Flag indicating whether the file
                                      ///< should be overwritten if it already
                                      ///< exists.
};

/**
 * @class TFileWriter
 * @brief Class responsible for writing a signal line to a file.
 */
class TFileWriter {
   public:
    /**
     * @brief Constructs a TFileWriter with a signal line and file path.
     *
     * @param signalLine Pointer to the signal line that will be written to the
     * file.
     * @param filePath Path to the file where the signal line will be
     * saved.
     * @param isRewriteEnabled Flag indicating whether the file should be
     * overwritten.
     */
    explicit TFileWriter(
        const TSignalLine* signalLine,
        std::string        filePath         = PM::DEFAULT_SIGNAL_LINE_FILEPATH,
        bool               isRewriteEnabled = FM::DEFAULT_REWRITE_ENABLED);

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
     * @brief Retrieves the parameters used for writing the signal line to a
     * file.
     *
     * @return const TFileWriterParams& A constant reference to the file writer
     * parameters.
     */
    [[nodiscard]] const TFileWriterParams& getParams() const;

    /**
     * @brief Checks if the file writing process has been executed.
     *
     * @return bool True if the file writing process has been executed, false
     * otherwise.
     */
    [[nodiscard]] bool isExecuted() const;

    /**
     * @brief Executes the file writing process.
     *
     * @throw SignalProcessingError If the signal line is not specified; if the
     * file already exists and is not empty, and the rewrite flag is disabled;
     * if the file cannot be opened for writing.
     */
    void execute() const;

   private:
    TFileWriterParams _params =
        {};  ///< Parameters for writing the signal line to the file.
    mutable bool _isExecuted = false;  ///< Flag indicating whether the file
                                       ///< writing process has been executed.
};