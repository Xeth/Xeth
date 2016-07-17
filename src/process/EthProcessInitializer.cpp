#include "EthProcessInitializer.hpp"

namespace Xeth{


void EthProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}

QString EthProcessInitializer::GetDefaultCommand()
{
    QString path = QCoreApplication::applicationDirPath();
#if defined(__WINDOWS_OS__)
    path.append("\\vendor\\bin\\geth.exe");
#else
    path.append("/vendor/bin/geth");
#endif

    QFileInfo info(path);
    if(info.exists())
    {
        return path;
    }
#if defined(__WINDOWS_OS__)
    return "geth.exe";
#else
    return "geth";
#endif
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
    args.push_back("--verbosity=0");

    if(! settings.get<int>("dao-fork", 1))
    {
        args.push_back("--oppose-dao-fork");
    }
    else
    {
        args.push_back("--support-dao-fork");
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
