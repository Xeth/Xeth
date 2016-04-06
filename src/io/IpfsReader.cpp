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
    process.waitForFinished();
    if(process.exitCode()!=0)
    {
        return QByteArray();
    }
    return process.readAllStandardOutput();
}


QJsonObject IpfsReader::readJson(const QString &hash)
{
    QJsonDocument document = QJsonDocument::fromBinaryData(readBytes(hash), QJsonDocument::BypassValidation);
    return document.object();
}


}
