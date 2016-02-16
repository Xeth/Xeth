
#include "ScanProgress.hpp"

namespace Xeth{

ScanProgress::ScanProgress() :
    _step(0),
    _value(0),
    _signalStep(1),
    _nextSignal(_signalStep)
{}

void ScanProgress::setRange(size_t minBlock, size_t maxBlock)
{
    _step = 100/(double)maxBlock;
    _nextSignal = _signalStep;
    _value = _step * (double)minBlock;
    emit Progress(_value);
}


void ScanProgress::setSignalStep(double step)
{
    _signalStep = step;
    _nextSignal = step;
}

void ScanProgress::next()
{
    _value+=_step;

    if(_value >= _nextSignal)
    {
        _nextSignal += _signalStep;
        if(_nextSignal > 100.0)
        {
            _nextSignal = 100.0;
        }

        emit Progress(_value);
    }
}

double ScanProgress::getValue() const
{
    return _value;
}

void ScanProgress::setValue(double value)
{
    _value = value>100.0? 100.0 : value;
    emit Progress(_value);
}


}
