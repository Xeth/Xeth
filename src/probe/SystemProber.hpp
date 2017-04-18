#pragma once

#include <vector>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QTimer>

#include "Probe.hpp"


namespace Xeth{



class SystemProber : public QObject
{
    Q_OBJECT

    public:

        SystemProber(const Settings &);
        ~SystemProber();

        template<class Probe>
        void addProbe();

        template<class Probe, class Args>
        void addProbe(const Args &);

        void loopAsync(time_t interval = 300000);

    public slots:
        bool run();

    signals:
        void Warning(const QString &) const;
        void Error(const QString &) const;
        void Success() const;


    private slots:
        void emitError(const QString &);
        void emitWarning(const QString &);

    private:
        void clear();
        void registerProbe(Probe *);

    private:
        typedef std::vector<Probe *> ProbeContainer;


        ProbeContainer _probers;
        const Settings  &_settings;
        QTimer _timer;
        time_t _interval;
};


}

#include "SystemProber.ipp"
