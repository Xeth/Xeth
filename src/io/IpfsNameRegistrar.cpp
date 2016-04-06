#include "IpfsNameRegistrar.hpp"


namespace Xeth{


IpfsNameRegistrar::IpfsNameRegistrar(const Settings &settings) : 
    _settings(settings)
{}


QString IpfsNameRegistrar::publish(const QString &hash)
{
    QProcess process;
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"name"<<"publish"<<hash);
    return execute(process);
}


QString IpfsNameRegistrar::resolve(const QString &name)
{
    QProcess process;
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"name"<<"resolve"<<name);
    return execute(process);
}


inline QString IpfsNameRegistrar::execute(QProcess &process)
{
    process.start();
    process.waitForFinished();
    if(process.exitCode()!=0)
    {
        return QString();
    }
    return process.readAllStandardOutput();
}


}
