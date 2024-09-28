#include "TFileWriter.h"
#include "TCore.h"
#include "TSignalLine.h"

#include <fstream>
#include <string>
#include <utility>

/**
 ** PUBLIC METHODS
 */

TFileWriter::TFileWriter(const TSignalLine* signalLine, std::string filePath)
    : _params{signalLine, std::move(filePath)} {}

TFileWriter::TFileWriter(TFileWriterParams params)
    : _params(std::move(params)) {}

const TFileWriterParams& TFileWriter::getParams() const {
  return _params;
}

void TFileWriter::execute() const {
  std::ofstream file(_params.filePath);
  if (!file.is_open()) {
    throw SignalProcesserException("Can't open file: \"" + _params.filePath +
                                   "\"");
  }
  if (_params.signalLine == nullptr) {
    throw SignalProcesserException("TSignalLine pointer is null");
  }
  Point point = {0.0, 0.0};
  for (int i = 0; i < _params.signalLine->getParams().pointsCount; i++) {
    point = _params.signalLine->getPoint(i);
    file << point.x << '\t' << point.y << '\n';
  }
  file.close();
}