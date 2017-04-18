#include "SystemProber.hpp"


namespace Xeth{


SystemProber::SystemProber(const Settings &settings) :
    _settings(settings)
{
    if(!QObject::connect(&_timer, &QTimer::timeout, this, &SystemProber::run))
    {
        throw std::runtime_error("failed to connect timeout signal");
    }
    
}


SystemProber::~SystemProber()
{
    clear();
}


void SystemProber::loopAsync(time_t interval)
{
    _timer.setInterval(interval);
    _timer.setSingleShot(false);
    _timer.start();
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

    emit Success();

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
    emit Error(msg);
}


void SystemProber::emitWarning(const QString &msg)
{
    emit Warning(msg);
}



}
