#include "IpfsProcessInitializer.hpp"

namespace Xeth{


void IpfsProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}

QString IpfsProcessInitializer::GetDefaultCommand()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/bin/");
#if defined(__WINDOWS_OS__)
    path.append("/windows-x64/ipfs.exe");
#elif defined(__LINUX_OS__)
    path.append("/linux-x64/ipfs");
#elif defined(__APPLE_OS__)
    path.append("/darwin-x64/ipfs");
#else
    #error "Invalid OS"
#endif
    return path;
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
