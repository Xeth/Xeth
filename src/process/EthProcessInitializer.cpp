#include "EthProcessInitializer.hpp"

namespace Xeth{


void EthProcessInitializer::Initialize(QProcess &process)
{
#ifdef __WINDOWS_OS__
    process.setProgram("geth.exe");
#else
    process.setProgram("geth");
#endif
}


void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    process.setProgram(GetCommand(settings));
    process.setArguments(GetArguments(settings));
}

QString EthProcessInitializer::GetCommand(const Settings &settings)
{
#ifdef __WINDOWS_OS__
    return settings.get("eth-command", "geth.exe");
#else
    return settings.get("eth-command", "geth");
#endif
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
