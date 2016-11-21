#include "UpdateEthereumClientCommand.hpp"



namespace Xeth{


UpdateEthereumClientCommand::UpdateEthereumClientCommand(ProcessSupervisor &client) : 
    _client(client)
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


    if(!QFile::copy(path, makeBinPath(vendors, info)))
    {
        throw std::runtime_error("failed to copy file");
    }

    _client.start();
    return QVariant::fromValue(true);
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
    QString path = QCoreApplication::applicationDirPath();
#if defined(__WINDOWS_OS__)
    path.append("\\vendor\\bin\\");
#else
    path.append("/vendor/bin/");
#endif
    return path;
}





}
