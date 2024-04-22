#ifndef TMULTIPLIER_H
#define TMULTIPLIER_H

#include "TSignalLine.h"

class TMultiplier {
	public:
		TMultiplier(TSignalLine* sl1, TSignalLine* sl2);
		TSignalLine *sl() const;
		void exec();
	private:
		TSignalLine* _sl;
		TSignalLine* _sl1;
		TSignalLine* _sl2;
};

#endif