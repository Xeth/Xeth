
#include "SystemFacade.hpp"

namespace Xeth{


SystemFacade::SystemFacade(const Settings &settings, Notifier &notifier, Invoker<Notifier>  &invoker) : 
    _settings(settings),
    _notifier(notifier),
    _invoker(invoker),
    _prober(_settings)
{
    QObject::connect(&_prober, &SystemProber::Error, this, &SystemFacade::emitError);
    QObject::connect(&_prober, &SystemProber::Warning, this, &SystemFacade::emitWarning);
    _prober.addProbe<HddProbe>();
}


const QStringList & SystemFacade::getErrors() const
{
    return _prober.getErrors();
}


const QStringList & SystemFacade::getWarnings() const
{
    return _prober.getWarnings();
}


void SystemFacade::emitError(const QString &msg)
{
    emit Error(msg);
}

void SystemFacade::emitWarning(const QString &msg)
{
    emit Warning(msg);
}

QString SystemFacade::getVersion() const
{
    return QString(XETH_VERSION);
}

QString SystemFacade::getNewerClientVersion() const
{
    return _newerClientVersion;
}


QString SystemFacade::getNewerXethVersion() const
{
    return _newerXethVersion;
}


QVariant SystemFacade::getClientVersion() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant SystemFacade::getClientVersionNumber() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, GetClientVersionCommand::Version_Only);
}

QVariant SystemFacade::getLatestReleaseInfo() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


Q_INVOKABLE QObject * SystemFacade::getLatestReleaseInfoAsync() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invokeAsync(command, NullCommandArguments());
}

void SystemFacade::fetchLatestReleaseDataAsync()
{
     QtConcurrent::run(this, &SystemFacade::fetchLatestReleaseData);
}

void SystemFacade::fetchLatestReleaseData()
{
    GetLastReleaseInfoCommand cmd;
    _latestData  = cmd.getJson();

    try
    {
        updateLatestReleaseInfo();
    }
    catch(...)
    {}
}


QVariant SystemFacade::updateLatestReleaseInfo()
{
    checkXethVersion(_latestData);
    checkClientVersion(_latestData);
    return QVariant::fromValue(true);
}


void SystemFacade::checkClientVersion(const QJsonObject &latestData)
{
    GetClientVersionCommand cmd(_settings);
    QString clientInfo = cmd();
    QString clientName, clientVersion;
    if(clientInfo.contains("Parity"))
    {
        clientName = "parity";
        clientVersion = clientInfo.mid(7, clientInfo.size());
    }
    else
    {
        clientName = "geth";
        clientVersion = clientInfo.mid(5, clientInfo.size());
    }

    QString latestVersion = latestData[clientName].toString();

    if(isNewVersion(clientVersion, latestVersion))
    {
        clientName.append(" ");
        _newerClientVersion = clientName + latestVersion;
    }
    else
    {
        _newerClientVersion = "";
    }
    _notifier.emitData("update", "client", _newerClientVersion);

}


void SystemFacade::checkXethVersion(const QJsonObject &latestData)
{
    QString version = XETH_VERSION;
    QString latestVersion = latestData["xeth"].toString();

    if(isNewVersion(version, latestVersion))
    {
        _newerXethVersion = latestVersion;
    }
    else
    {
        _newerXethVersion = "";
    }
    _notifier.emitData("update", "xeth", latestVersion);
}

bool SystemFacade::isNewVersion(const QString &current, const QString &latest)
{
    return normalizeVersionNumber(current) < normalizeVersionNumber(latest);
}


qulonglong SystemFacade::normalizeVersionNumber(const QString &str)
{
    QString normalized;
    int parsed = 0;
    int digits = 0;

    for(int i = 0; i < str.size(); i++)
    {
        if(str[i].isDigit())
        {
            normalized.append(str[i]);
            digits ++;
        }
        else
        {
            for(int j=digits; j<4; j++)
            {
                normalized.append('0');
            }

            digits = 0;
            parsed++;
            if(parsed > 2)
            {
                break;
            }
        }
    }
    if(parsed < 3)
    {
        for(int j=digits; j<4; j++)
        {
            normalized.append('0');
        }
    }
    return normalized.toULongLong();
}

}
