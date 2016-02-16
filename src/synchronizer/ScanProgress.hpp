#pragma once

#include <stdlib.h>

#include <QObject>

namespace Xeth{


class ScanProgress : public QObject
{
    Q_OBJECT

    public:

        ScanProgress();

        void setSignalStep(double);

        void setRange(size_t min, size_t max);
        void next();

        double getValue() const;
        void setValue(double);

    signals:
        void Progress(double) const;

    private:
        double _step;
        double _value;
        double _signalStep;
        double _nextSignal;
};


class DummyScanProgress
{
    public:
        inline void setRange(size_t, size_t){}
        inline void next() {}
        inline double getValue() {return 0;}
        inline void setValue(double){}
};


}

