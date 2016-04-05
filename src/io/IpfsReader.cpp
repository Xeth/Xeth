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
        throw std::runtime_error("failed to write on ipfs");
    }
    return process.readAllStandardOutput();
}


QJsonObject IpfsReader::readJson(const QString &hash)
{
    QJsonDocument document = QJsonDocument::fromBinaryData(readBytes(hash));
    return document.object();
}


}
