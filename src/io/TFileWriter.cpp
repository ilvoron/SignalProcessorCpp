#include "TCore.h"
#include "TFileWriter.h"
#include <fstream>

// PUBLIC

TFileWriter::TFileWriter(const TSignalLine* signalLine, const std::string& filePath)
	: _params{signalLine, filePath} {}

TFileWriter::TFileWriter(TFileWriterParams params)
	: _params(params) {}

const TFileWriterParams& TFileWriter::getParams() const { return _params; }

void TFileWriter::execute() {
	std::ofstream file(_params.filePath);
	if (!file.is_open()) { THROW_SIGNAL_PROCESSOR_EXCEPTION("Can't open file: \"" + _params.filePath + "\""); }
	if (_params.signalLine == nullptr) { THROW_SIGNAL_PROCESSOR_EXCEPTION("TSignalLine pointer is null"); }
	Point point;
	for (int i = 0; i < _params.signalLine->getParams().pointsCount; i++) {
		point = _params.signalLine->getPoint(i);
		file << point.x << '\t' << point.y << '\n';
	}
	file.close();
}