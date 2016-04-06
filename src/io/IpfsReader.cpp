#include "IpfsReader.hpp"

namespace Xeth{


IpfsReader::IpfsReader(const Settings &settings):
    _settings(settings)
{}


QByteArray IpfsReader::readBytes(const QString &hash)
{
    QProcess process;
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"cat"<<hash);
    process.start();
    process.waitForFinished(3000000);
    if(process.exitCode()!=0)
    {
        return QByteArray();
    }
    return process.readAllStandardOutput();
}


QJsonObject IpfsReader::readJson(const QString &hash)
{
    QByteArray result = readBytes(hash);
    QJsonDocument document = QJsonDocument::fromJson(result);
    return document.object();
}


}
