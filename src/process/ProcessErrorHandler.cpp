#include "ProcessErrorHandler.hpp"
#include <QDebug>

namespace Xeth{


ProcessErrorHandler::ProcessErrorHandler(ProcessSupervisor &process, size_t limit) : 
    _process(process),
    _limit(limit),
    _errors(0)
{}


void ProcessErrorHandler::operator()()
{
    operator()("process failed: too many restarts");
}


void ProcessErrorHandler::operator()(const char *error)
{
    if(++_errors > _limit)
    {
        throw std::runtime_error(error);
    }
    qDebug()<<"restarting "<<_process.getProgram()<<" process";
    _process.restart();
}


}
