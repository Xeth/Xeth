#include "EthProcessInitializer.hpp"
#include "database/EthereumKeyStorePath.hpp"
#include "io/ApplicationPath.hpp"

#include <QDebug>
#include <QDir>

namespace Xeth{


void EthProcessInitializer::Initialize(QProcess &process)
{
    process.setProgram(GetDefaultCommand());
}


QString EthProcessInitializer::GetVendorPath(const QString &rootPath, const char *name)
{
    QString path = rootPath;
#if defined(__WINDOWS_OS__)
    path.append("\\");
    path.append(name);
    path.append(".exe");
#else
    path.append("/");
    path.append(name);
#endif

    return path;
}


QString EthProcessInitializer::GetVendorPath(const char *name)
{
    return GetVendorPath(ApplicationPath::Vendors(), name);
}


QString EthProcessInitializer::GetLocalVendorPath(const char *name)
{
    return GetVendorPath(ApplicationPath::LocalVendors(), name);
}


bool EthProcessInitializer::FileExists(const QString &path)
{
    QFileInfo info(path);
    return info.exists();
}


QString EthProcessInitializer::GetDefaultCommand()
{
    QString parityPath = GetLocalVendorPath("parity");

    if(FileExists(parityPath))
    {
        return parityPath;
    }

    QString gethPath = GetLocalVendorPath("geth");
    if(FileExists(gethPath))
    {
        return gethPath;
    }

    parityPath = GetVendorPath("parity");
    if(FileExists(parityPath))
    {
        return parityPath;
    }

    gethPath = GetVendorPath("geth");
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


QString EthProcessInitializer::GetCommand(const Settings &settings)
{
    if(settings.has("command"))
    {
        return settings.get("command");
    }
    //else
    return GetDefaultCommand();
}


QStringList EthProcessInitializer::GetGethArguments(const Settings &settings)
{
    QStringList args;

    args.push_back("--verbosity=0");
    args.push_back("--cache=1024");
    args.push_back("--targetgaslimit=1500000");
    args.push_back("--gasprice=20000000000");

    QString keystoreOpt = "--keystore=";
    keystoreOpt += ApplicationPath::EthereumData();
    keystoreOpt += QDir::separator();
    keystoreOpt += "keystore";
    keystoreOpt += QDir::separator();
    if(settings.get<bool>("testnet", false))
    {
        args.push_back("--testnet");
        keystoreOpt += "testnet";
    }
    else
    {
        keystoreOpt += "ethereum";
    }
    args.push_back(keystoreOpt);


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
    return args;
}



QStringList EthProcessInitializer::GetParityArguments(const Settings &settings)
{
    QStringList args;

    args.push_back("--geth");
    args.push_back("--no-dapps");
    args.push_back("--pruning=archive");
    args.push_back("--cache-size-db=1024");
    args.push_back("--gas-floor-target=1500000");
    args.push_back("--gasprice=20000000000");
    args.push_back("--gas-cap=1500000");

    QString keystoreOpt = "--keys-path=";
    keystoreOpt += ApplicationPath::EthereumData();
    keystoreOpt += QDir::separator();
    keystoreOpt += "keystore";

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

    args.push_back(keystoreOpt);


    qDebug()<<"args="<<args;

    return args;
}

QStringList EthProcessInitializer::GetArguments(const QString &command, const Settings &settings)
{
    QStringList args;

    if(command.contains(QRegExp("parity")))
    {
        return GetParityArguments(settings);

    }
    return GetGethArguments(settings);
}

void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings)
{
    SetEnvironment(process);
    QString command = GetCommand(settings);
    process.setProgram(command);
    process.setArguments(GetArguments(command, settings));
}


void EthProcessInitializer::Initialize(QProcess &process, const Settings &settings, const QStringList &extraArgs)
{
    SetEnvironment(process);
    QString command = GetCommand(settings);
    process.setProgram(command);
    QStringList args = GetArguments(command, settings);
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
    setenv("PATH", path.toLatin1().constData(), true);
#endif
}






}
