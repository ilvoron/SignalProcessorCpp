#ifndef TDERIVATIVE_H
#define TDERIVATIVE_H

#include "TSignalLine.h"

class TDerivative {
	public:
		TDerivative(TSignalLine* sl);
		TSignalLine* sl() const;
		void exec();
	private:
		TSignalLine* _sl_in;
		TSignalLine* _sl_out;
};

#endif