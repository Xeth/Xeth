#include "EthProcessInitializer.hpp"
#include "database/EthereumKeyStorePath.hpp"
#include <QDebug>

namespace Xeth{


void EthProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}


QString EthProcessInitializer::GetVendorPath(const QString &rootPath, const char *name)
{

    QString path = rootPath;

#if defined(__WINDOWS_OS__)
    path.append("\\vendor\\bin\\");
    path.append(name);
    path.append(".exe");
#else
    path.append("/vendor/bin/");
    path.append(name);
#endif

    return path;
}


QString EthProcessInitializer::GetVendorPath(const char *name)
{
    QString rootPath = QCoreApplication::applicationDirPath();
    return GetVendorPath(rootPath, name);
}


bool EthProcessInitializer::FileExists(const QString &path)
{
    QFileInfo info(path);
    return info.exists();
}


QString EthProcessInitializer::GetDefaultCommand()
{
    QString rootPath = QCoreApplication::applicationDirPath();
    QString parityPath = GetVendorPath(rootPath, "parity");

    if(FileExists(parityPath))
    {
        return parityPath;
    }

    QString gethPath = GetVendorPath(rootPath, "geth");
    if(FileExists(gethPath))
    {
        return gethPath;
    }

#if defined(__DEFAULT_ETH_COMMAND__)
    return __DEFAULT_ETH_COMMAND__;
#else
#if defined(__WINDOWS_OS__)
    return "C:\\Program Files\\Ethcore\\Parity\\parity.exe";
#else
    return "parity";
#endif
#endif
}

void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    SetEnvironment(process);
    process.setProgram(GetCommand(settings));
    process.setArguments(GetArguments(settings));
}

QString EthProcessInitializer::GetCommand(const Settings &settings)
{
    if(settings.has("command"))
    {
        return settings.get("command");
    }
    //else
    return GetDefaultCommand();
}

QStringList EthProcessInitializer::GetArguments(const Settings &settings)
{
    QStringList args;

    if(!settings.has("command")||QString(settings.get("command")).contains(QRegExp("parity")))
    {

        if(settings.get<bool>("testnet", false))
        {
            args.push_back("--chain=morden");
        }
        else
        {
            if(! settings.get<int>("dao-fork", 1))
            {
                args.push_back("--chain=homestead-dogmatic");
            }
        }
        args.push_back("--geth");
        args.push_back("--no-dapps");
        args.push_back("--pruning=archive");
        args.push_back("--cache-size-db=1024");
        args.push_back("--gas-floor-target=1500000");
        args.push_back("--gasprice=20000000000");
        args.push_back("--gas-cap=1500000");
        EthereumKeyStorePath path(settings);
        QString pathArg = "--keys-path=";
        pathArg += path.toString().c_str();
        args.push_back(pathArg);
    }
    else
    {

        if(settings.get<bool>("testnet", false))
        {
            args.push_back("--testnet");
        }
        args.push_back("--verbosity=0");
        args.push_back("--cache=1024");
        args.push_back("--targetgaslimit=1500000");
        args.push_back("--gasprice=20000000000");

        if(! settings.get<int>("dao-fork", 1))
        {
            args.push_back("--oppose-dao-fork");
        }
        else
        {
            args.push_back("--support-dao-fork");
        }

        if(settings.get<int>("fast", 1))
        {
            args.push_back("--fast");
        }

    }
    return args;
}

void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings, const QStringList &extraArgs)
{
    SetEnvironment(process);
    process.setProgram(GetCommand(settings));
    QStringList args = GetArguments(settings);
    args.append(extraArgs);
    process.setArguments(args);
}


void EthProcessInitializer::SetEnvironment(QProcess &process)
{
#if  defined(__APPLE_OS__)
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString path = env.value("PATH");
    if(path != "") path += ":";
    path += "/usr/local/bin:/usr/bin:~/.multirust/toolchains/stable/cargo/bin";
    env.remove("PATH");
    env.insert("PATH", path);

    process.setProcessEnvironment(env);
#endif
}






}
