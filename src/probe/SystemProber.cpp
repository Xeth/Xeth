#include "SystemProber.hpp"


namespace Xeth{


SystemProber::SystemProber(const Settings &settings) :
    _settings(settings)
{}


SystemProber::~SystemProber()
{
    clear();
}


const SystemProber::Errors & SystemProber::getErrors() const
{
    return _errors;
}


const SystemProber::Warnings & SystemProber::getWarnings() const
{
    return _warnings;
}


bool SystemProber::run()
{
    for(ProbeContainer::iterator it = _probers.begin(), end = _probers.end(); it!=end; ++it)
    {
        Probe & probe = **it;
        if(!probe(_settings))
        {
            return false;
        }
    }

    return true;
}


void SystemProber::clear()
{
    for(ProbeContainer::iterator it = _probers.begin(), end = _probers.end(); it!=end; ++it)
    {
        delete *it;
    }

    _probers.clear();
}


void SystemProber::registerProbe(Probe *probe)
{
    _probers.push_back(probe);
    QObject::connect(probe, &Probe::Error, this, &SystemProber::emitError);
    QObject::connect(probe, &Probe::Warning, this, &SystemProber::emitWarning);
}


void SystemProber::emitError(const QString &msg)
{
    _errors.push_back(msg);
    emit Error(msg);
}


void SystemProber::emitWarning(const QString &msg)
{
    _warnings.push_back(msg);
    emit Warning(msg);
}



}
