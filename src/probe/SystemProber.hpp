#pragma once

#include <vector>
#include <QString>
#include <QStringList>
#include <QObject>

#include "Probe.hpp"


namespace Xeth{



class SystemProber : public QObject
{
    Q_OBJECT

    public:
        typedef QStringList MsgContainer;
        typedef MsgContainer Errors;
        typedef MsgContainer Warnings;

    public:

        SystemProber(const Settings &);
        ~SystemProber();

        template<class Probe>
        void addProbe();

        template<class Probe, class Args>
        void addProbe(const Args &);

        bool run();

        const Errors & getErrors() const;
        const Warnings & getWarnings() const;

    signals:
        void Warning(const QString &) const;
        void Error(const QString &) const;


    private slots:
        void emitError(const QString &);
        void emitWarning(const QString &);

    private:
        void clear();
        void registerProbe(Probe *);

    private:
        typedef std::vector<Probe *> ProbeContainer;


        ProbeContainer _probers;
        MsgContainer   _warnings;
        MsgContainer   _errors;
        const Settings  &_settings;
};


}

#include "SystemProber.ipp"
