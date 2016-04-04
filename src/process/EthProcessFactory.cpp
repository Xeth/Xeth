#include "EthProcessFactory.hpp"

namespace Xeth{


QProcess * EthProcessFactory::Create()
{
    QProcess *process = new QProcess;
    EthProcessInitializer::Initialize(*process);
    return process;
}


QProcess * EthProcessFactory::Create(const Settings &settings)
{
    QProcess *process = new QProcess;
    EthProcessInitializer::Initialize(*process, settings);
    return process;
}








}
