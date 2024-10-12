/**
 * @file TFileWriter.cpp
 * @author Vorontsov Ilya Aleksandrovich (ilvoron)
 * @brief Contains the implementation of the TFileWriter class, responsible for
 * writing signal lines to files.
 * @version 2.1.0.1
 * @date October 12, 2024
 * @copyright Copyright (c) 2024
 */

#include "TFileWriter.hpp"
#include "TCore.hpp"
#include "TSignalLine.hpp"

#include <cstddef>
#include <fstream>
#include <string>
#include <utility>

/*
 * PUBLIC METHODS
 */

TFileWriter::TFileWriter(const TSignalLine* signalLine,
                         std::string        filePath,
                         const bool         isRewriteEnabled)
    : _params{.signalLine       = signalLine,
              .filePath         = std::move(filePath),
              .isRewriteEnabled = isRewriteEnabled} {}

TFileWriter::TFileWriter(TFileWriterParams params)
    : _params(std::move(params)) {}

const TFileWriterParams& TFileWriter::getParams() const {
    return _params;
}

bool TFileWriter::isExecuted() const {
    return _isExecuted;
}

void TFileWriter::execute() const {
    _isExecuted = false;

    // We're ensuring that the signal line is not null here because the signal
    // line may be set after the TFileWriter object creation.
    if (_params.signalLine == nullptr) {
        throw SignalProcessingError("Signal line is not specified.");
    }

    // Check if the file already exists and is not empty
    std::ifstream fileCheck(_params.filePath);
    if (fileCheck.is_open() &&
        fileCheck.peek() != std::ifstream::traits_type::eof()) {
        fileCheck.close();
        if (!_params.isRewriteEnabled) {
            throw SignalProcessingError(
                "File already exists and is not empty: \"" + _params.filePath +
                "\"");
        }
    } else {
        fileCheck.close();
    }

    // Proceed with writing to the file
    std::ofstream file(_params.filePath);
    if (!file.is_open()) {
        throw SignalProcessingError("Can't open file: \"" + _params.filePath +
                                    "\"");
    }

    for (std::size_t i = 0; i < _params.signalLine->getParams().pointsCount;
         ++i) {
        auto [x, y] = _params.signalLine->getPoint(i);
        file << x << '\t' << y << '\n';
    }

    file.close();
    _isExecuted = true;
}