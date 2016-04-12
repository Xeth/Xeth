#include "IpfsReader.hpp"


namespace Xeth{


IpfsReader::IpfsReader(const Settings &settings):
    _settings(settings)
{}


QByteArray IpfsReader::readBytes(const QString &hash)
{
    for(int i=0; i<10; i++)
    {
        QProcess process;
        IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"cat"<<hash);
        process.start();
        process.waitForFinished(6000000);
        if(process.exitCode()!=0)
        {
            boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
            continue;
        }
        QByteArray result = process.readAllStandardOutput();
        return result;
    }
    return QByteArray();
}


QJsonObject IpfsReader::readJson(const QString &hash)
{
    QByteArray result = readBytes(hash);
    QJsonDocument document = QJsonDocument::fromJson(result);
    return document.object();
}


}
