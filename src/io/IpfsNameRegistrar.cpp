#include "IpfsNameRegistrar.hpp"


namespace Xeth{


IpfsNameRegistrar::IpfsNameRegistrar(const Settings &settings) : 
    _settings(settings)
{}


QString IpfsNameRegistrar::publish(const QString &hash)
{
    QProcess process;
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"name"<<"publish"<<hash);
    QString result = execute(process);
    result.remove(0, 13);
    result.remove(46, result.length()-46);
    return result;
}


QString IpfsNameRegistrar::resolve(const QString &name)
{
    QProcess process;
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"name"<<"resolve"<<name);
    QString result = execute(process);
    result.remove(0,6);
    result.remove(result.length()-1, 1);
    return result;
}


inline QString IpfsNameRegistrar::execute(QProcess &process)
{
    process.start();
    process.waitForFinished(3000000);
    if(process.exitCode()!=0)
    {
        return QString();
    }
    return process.readAllStandardOutput();
}


}
