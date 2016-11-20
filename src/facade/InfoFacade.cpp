
#include "InfoFacade.hpp"

namespace Xeth{


InfoFacade::InfoFacade(const Settings &settings, Notifier &notifier, Invoker<Notifier>  &invoker) : 
    _settings(settings),
    _notifier(notifier),
    _invoker(invoker)
{}


QString InfoFacade::getVersion() const
{
    return QString(XETH_VERSION);
}

QString InfoFacade::getNewerClientVersion() const
{
    return _newerClientVersion;
}


QString InfoFacade::getNewerXethVersion() const
{
    return _newerXethVersion;
}


QVariant InfoFacade::getClientVersion() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, NullCommandArguments());
}


QVariant InfoFacade::getClientVersionNumber() const
{
    GetClientVersionCommand command(_settings);
    return _invoker.invoke(command, GetClientVersionCommand::Version_Only);
}

QVariant InfoFacade::getLatestReleaseInfo() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invoke(command, NullCommandArguments());
}


Q_INVOKABLE QObject * InfoFacade::getLatestReleaseInfoAsync() const
{
    GetLastReleaseInfoCommand command;
    return _invoker.invokeAsync(command, NullCommandArguments());
}

void InfoFacade::checkVersionAsync()
{
     QtConcurrent::run(this, &InfoFacade::checkVersion);
}

void InfoFacade::checkVersion()
{
    GetLastReleaseInfoCommand cmd;
    QJsonObject latestData  = cmd.getJson();

    try
    {
        checkXethVersion(latestData);
        checkClientVersion(latestData);
    }
    catch(...)
    {}
}


void InfoFacade::checkClientVersion(const QJsonObject &latestData)
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
        _notifier.emitData("version", "client", _newerClientVersion);
    }

}


void InfoFacade::checkXethVersion(const QJsonObject &latestData)
{
    QString version = XETH_VERSION;
    QString latestVersion = latestData["xeth"].toString();

    if(isNewVersion(version, latestVersion))
    {
        _newerXethVersion = latestVersion;
        _notifier.emitData("version", "xeth", latestVersion);
    }
}

bool InfoFacade::isNewVersion(const QString &current, const QString &latest)
{
    return normalizeVersionNumber(current) < normalizeVersionNumber(latest);
}


qulonglong InfoFacade::normalizeVersionNumber(const QString &str)
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
