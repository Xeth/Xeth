#include "IpfsProcessInitializer.hpp"

namespace Xeth{


void IpfsProcessInitializer::Initialize(QProcess &process)
{
#ifdef __WINDOWS_OS__
    process.setProgram("ipfs.exe");
#else
    process.setProgram("ipfs");
#endif
}


void IpfsProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    process.setProgram(GetCommand(settings));
}

QString IpfsProcessInitializer::GetCommand(const Settings &settings)
{
#ifdef __WINDOWS_OS__
    return settings.get("ipfs-command", "ipfs.exe");
#else
    return settings.get("ipfs-command", "ipfs");
#endif
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
