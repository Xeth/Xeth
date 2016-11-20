#include "GetClientVersionCommand.hpp"


namespace Xeth{


GetClientVersionCommand::GetClientVersionCommand(const Settings  &settings) : 
    _settings(settings)
{}


QString GetClientVersionCommand::operator()() const
{
    QProcess *process = EthProcessFactory::Create(_settings);
    process->deleteLater();

    if(isParity(process))
    {
        return getParityVersion(process);
    }

    return getGethVersion(process);
}


bool GetClientVersionCommand::isParity(QProcess *process) const
{
    return process->program().contains("parity");
}

QString GetClientVersionCommand::getParityVersion(QProcess *process) const
{
    return getClientVersion(process, "--version", "Parity/(.*)+\\n", "Parity ");
}


QString GetClientVersionCommand::getGethVersion(QProcess *process) const
{
    return getClientVersion(process, "version", "Version: (.*)+\\n", "Geth ");
}


QString GetClientVersionCommand::getClientVersion(QProcess *process, const QString &argument, const QString &pattern, const QString &name) const
{
    QStringList args = process->arguments();
    args.append(argument);
    process->setArguments(args);
    process->start();
    process->waitForFinished();
    QString output  = process->readAllStandardOutput();
    QRegExp regexp = QRegExp(pattern);
    regexp.setMinimal(true);
    regexp.indexIn(output);
    QStringList result = regexp.capturedTexts();
    return name + (result.size() > 1 ? result[1] : "");
}



}
