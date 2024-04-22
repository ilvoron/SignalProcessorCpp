#ifndef TSUMMATOR_H
#define TSUMMATOR_H

#include "TSignalLine.h"

class TSummator {
	public:
		TSummator(TSignalLine* sl1, TSignalLine* sl2);
		TSignalLine *sl() const;
		void exec();
	private:
		TSignalLine* _sl;
		TSignalLine* _sl1;
		TSignalLine* _sl2;
};

#endif