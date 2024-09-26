#include "TCore.h"
#include "TSummator.h"

// PUBLIC

TSummator::TSummator(const TSignalLine* signalLine1,
                     const TSignalLine* signalLine2,
                     double inaccuracy,
                     std::string xLabel,
                     std::string yLabel,
                     std::string graphLabel)
	: _params{signalLine1, signalLine2, inaccuracy, xLabel, yLabel, graphLabel} {}

TSummator::TSummator(TSummatorParams params)
	: _params(params) {}

const TSignalLine* TSummator::getSignalLine() const {
	if (!_isExecuted) THROW_SIGNAL_PROCESSOR_EXCEPTION("Summator not executed");
	return _sl.get();
}

const TSummatorParams& TSummator::getParams() const { return _params; }

bool TSummator::isExecuted() const { return _isExecuted; }

void TSummator::execute() {
	if (_params.signalLine1 == nullptr || _params.signalLine2 == nullptr) THROW_SIGNAL_PROCESSOR_EXCEPTION("Invalid signal lines (nullptr)");
	if (!_params.signalLine1->equals(_params.signalLine2, _params.inaccuracy)) THROW_SIGNAL_PROCESSOR_EXCEPTION("Signal lines aren't equal");
	_sl = std::make_unique<TSignalLine>(_params.signalLine1->getParams().pointsCount, _params.xLabel, _params.yLabel, _params.graphLabel);
	double x, y;
	for (int i = 0; i < _params.signalLine1->getParams().pointsCount; i++) {
		x = _params.signalLine1->getPoint(i).x;
		y = _params.signalLine1->getPoint(i).y + _params.signalLine2->getPoint(i).y;
		_sl->setPoint(i, x, y);
	}
	_isExecuted = true;
}