#include "TFileWriter.h"
#include <fstream>

// ************
//    PUBLIC
// ************

TFileWriter::TFileWriter(TSignalLine* sl, std::string filePath) {
	_sl = sl;
	_filePath = filePath;
}

void TFileWriter::exec() {
	std::ofstream file;
	file.open(_filePath);
	unsigned int pointsCount = _sl->pointsCount();
	double x, y;
	for (int i = 0; i < pointsCount; i++) {
		x = _sl->at(i).x;
		y = _sl->at(i).y;
		file << x << '\t' << y << '\n';
	}
	file.close();
}