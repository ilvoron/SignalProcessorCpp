#ifndef TFILEWRITER_H
#define TFILEWRITER_H

#include "TSignalLine.h"
#include <string>

class TFileWriter {
	public:
		TFileWriter(TSignalLine* sl, std::string filePath);
		void exec();
	private:
		TSignalLine* _sl;
		std::string _filePath;
};

#endif