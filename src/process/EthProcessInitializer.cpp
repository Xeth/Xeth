#include "EthProcessInitializer.hpp"

namespace Xeth{


void EthProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}

QString EthProcessInitializer::GetDefaultCommand()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/bin/");
#if defined(__WINDOWS_OS__)
    path.append("/windows-x64/geth.exe");
#elif defined(__LINUX_OS__)
    path.append("/linux-x64/geth");
#elif defined(__APPLE_OS__)
    path.append("/darwin-x64/geth");
#else
    #error "Invalid OS"
#endif
    return path;
}

void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    process.setProgram(GetCommand(settings));
    process.setArguments(GetArguments(settings));
}

QString EthProcessInitializer::GetCommand(const Settings &settings)
{
    if(settings.has("eth"))
    {
        return settings.get("eth");
    }
    //else
    return GetDefaultCommand();
}

QStringList EthProcessInitializer::GetArguments(const Settings &settings)
{
    QStringList args;

    if(settings.get<bool>("testnet", false))
    {
        args.push_back("--testnet");
    }

    return args;
}

void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings, const QStringList &extraArgs)
{
    process.setProgram(GetCommand(settings));
    QStringList args = GetArguments(settings);
    args.append(extraArgs);
    process.setArguments(args);
}







}
