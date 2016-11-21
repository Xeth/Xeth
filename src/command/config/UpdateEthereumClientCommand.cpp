#include "UpdateEthereumClientCommand.hpp"
#include <QDebug>


namespace Xeth{


UpdateEthereumClientCommand::UpdateEthereumClientCommand(ProcessSupervisor &client, const Settings &settings) : 
    _client(client),
    _settings(settings)
{}


QVariant UpdateEthereumClientCommand::operator()(const QString &path)
{
    QFileInfo info(path);
    if(!info.isExecutable())
    {
        throw std::runtime_error("file is not executable");
    }

    QString name = info.baseName();

    if( name!="parity" && name!= "geth")
    {
        throw std::runtime_error("client not known, please use parity or geth");
    }

    _client.stop();

    QString vendors = getVendorsPath();

    backupIfExists(vendors, "parity");
    backupIfExists(vendors, "geth");

    createIfNotExists(vendors);


    qDebug()<<"copy "<<path<<" to "<<makeBinPath(vendors, info);

    if(!QFile::copy(path, makeBinPath(vendors, info)))
    {
        throw std::runtime_error("failed to copy file");
    }

    _client.attach(EthProcessFactory::Create(_settings));
    return QVariant::fromValue(true);
}


void UpdateEthereumClientCommand::createIfNotExists(const QString &path)
{
    boost::filesystem::path p = path.toStdString();
    if(!boost::filesystem::exists(p))
    {
        boost::filesystem::create_directories(p);
    }
}


void UpdateEthereumClientCommand::backupIfExists(const QString &path, const QString &name)
{
    QString file = path;
#if defined(__WINDOWS_OS__)
    file += "\\";
#else 
    file += "/";
#endif

    file += name;

#if defined(__WINDOWS_OS__)
    file += ".exe";
#endif

    QString backup = file;
    file += ".backup";

    qDebug()<<"file="<<file<<" backup : "<<backup;

    QFile::copy(file, backup);
}



QString UpdateEthereumClientCommand::makeBinPath(const QString &path, const QFileInfo &info)
{
    QString result = path;
#if defined(__WINDOWS_OS__)
    result += "\\";
#else 
    result += "/";
#endif
    result += info.fileName();
    return result;
}


QString UpdateEthereumClientCommand::getVendorsPath()
{
    return ApplicationPath::LocalVendors();
}





}
