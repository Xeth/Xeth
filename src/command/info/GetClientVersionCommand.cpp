#include "GetClientVersionCommand.hpp"

namespace Xeth{



GetClientVersionCommand::GetClientVersionCommand(const Settings  &settings) : 
    _settings(settings)
{}


QString GetClientVersionCommand::operator()(Format format) const
{
    QProcess *process = EthProcessFactory::Create(_settings);
    process->deleteLater();

    if(isParity(process))
    {
        return getParityVersion(process, format);
    }

    return getGethVersion(process, format);
}


bool GetClientVersionCommand::isParity(QProcess *process) const
{
    return process->program().contains("parity");
}

QString GetClientVersionCommand::getParityVersion(QProcess *process, Format format) const
{
    if(format==Full_Text)
    {
        return getParityVersion(process, "Parity ");
    }
    return getParityVersion(process, "");
}


QString GetClientVersionCommand::getParityVersion(QProcess *process, const QString &prepend) const
{
    return getClientVersion(process, "--version", ".*Parity/v(.+)\\n", prepend);
}


QString GetClientVersionCommand::getGethVersion(QProcess *process, Format format) const
{
    if(format==Full_Text)
    {
        return getGethVersion(process, "Geth ");
    }
    return getGethVersion(process, "");
}


QString GetClientVersionCommand::getGethVersion(QProcess *process, const QString &prepend) const
{
    return getClientVersion(process, "version", "Version: (.*)+\\n", prepend);
}


QString GetClientVersionCommand::getClientVersion(QProcess *process, const QString &argument, const QString &pattern, const QString &name) const
{
    QStringList args = process->arguments();
    args.append(argument);
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString output  = process->readAllStandardOutput();
    output += process->readAllStandardError();
    QRegExp regexp = QRegExp(pattern);
    regexp.setMinimal(true);
    regexp.indexIn(output);
    QStringList result = regexp.capturedTexts();
    return name + (result.size() > 1 ? result[1] : "");
}



}
