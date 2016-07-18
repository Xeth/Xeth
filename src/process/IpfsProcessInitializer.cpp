#include "IpfsProcessInitializer.hpp"

namespace Xeth{


void IpfsProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}

QString IpfsProcessInitializer::GetDefaultCommand()
{
#if defined(__IPFS_PATH__)
    return __IPFS_PATH__;
#else
    QString path = QCoreApplication::applicationDirPath();
#if defined(__WINDOWS_OS__)
    path.append("\\vendor\\bin\\ipfs.exe");
#else
    path.append("/vendor/bin/ipfs");
#endif

    QFileInfo info(path);
    if(info.exists())
    {
        return path;
    }

#if defined(__WINDOWS_OS__)
    return "ipfs.exe";
#else
    return "ipfs";
#endif
#endif
}

void IpfsProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    process.setProgram(GetCommand(settings));
}

QString IpfsProcessInitializer::GetCommand(const Settings &settings)
{
    if(settings.has("ipfs"))
    {
        return settings.get("ipfs");
    }
    //else
    return GetDefaultCommand();
}


void IpfsProcessInitializer::Initialize(QProcess &process, const Settings &settings, const QStringList &args)
{
    process.setProgram(GetCommand(settings));
    process.setArguments(args);
}


QStringList IpfsProcessInitializer::GetDaemonArguments()
{
    QStringList args;
    args.push_back("daemon");
    return args;
}


void IpfsProcessInitializer::InitializeDaemon(QProcess &process)
{
    Initialize(process);
    process.setArguments(GetDaemonArguments());
}


void IpfsProcessInitializer::InitializeDaemon(QProcess &process, const Settings &settings)
{
    process.setProgram(GetCommand(settings));
    process.setArguments(GetDaemonArguments());
}




void IpfsProcessInitializer::InitializeDaemon(QProcess &process, const Settings &settings, const QStringList &extraArgs)
{
    process.setProgram(GetCommand(settings));
    QStringList args = GetDaemonArguments();
    args.append(extraArgs);
    process.setArguments(args);
}






}
