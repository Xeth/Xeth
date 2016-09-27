#include "IpfsProcessFactory.hpp"


namespace Xeth{


//QProcess * IpfsProcessFactory::Create()
//{
//    QProcess *process = new QProcess;
//    IpfsProcessInitializer::Initialize(*process);
//    return process;
//}


//QProcess * IpfsProcessFactory::Create(const Settings &settings)
//{
//    QProcess *process = new QProcess;
//    IpfsProcessInitializer::Initialize(*process, settings);
//    return process;
//}


QProcess * IpfsProcessFactory::CreateDaemon()
{
    QProcess *process = new QProcess;
    IpfsProcessInitializer::InitializeDaemon(*process);
    return process;
}


QProcess * IpfsProcessFactory::CreateDaemon(const Settings &settings)
{
    QProcess *process = new QProcess;
    IpfsProcessInitializer::InitializeDaemon(*process, settings);
    return process;
}






}
