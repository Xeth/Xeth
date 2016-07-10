#include "IpfsWriter.hpp"


namespace Xeth{


IpfsWriter::IpfsWriter(const Settings &settings) : 
    _settings(settings)
{}


QString IpfsWriter::writeData(const QVariantMap &content)
{
    return writeData(QJsonObject::fromVariantMap(content));
}


QString IpfsWriter::writeData(const QJsonObject &content)
{
    QJsonDocument document(content);
    return writeData(document.toJson(QJsonDocument::Compact));
}


QString IpfsWriter::writeData(const QString &content)
{
    return writeData(content.toLocal8Bit());
}


QString IpfsWriter::writeFile(const QString &path)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"add"<<"-q"<<path);
    return execute(process);
}


QString IpfsWriter::writeData(const QByteArray &content)
{
    QTemporaryFile temp;
    temp.setAutoRemove(false);
    if(!temp.open())
    {
        return QString();
    }

    temp.write(content);

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    temp.close();
    IpfsProcessInitializer::Initialize(process, _settings, QStringList()<<"add"<<"-q"<<temp.fileName());

    return execute(process);
}


inline QString IpfsWriter::execute(QProcess &process)
{
    process.start();
    process.waitForFinished();
    if(process.exitCode()!=0)
    {
        return QString();
    }
    return QString(process.readAllStandardOutput()).remove(QRegExp("[\\n\\t\\r]"));
}






}
