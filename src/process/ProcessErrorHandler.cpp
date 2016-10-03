#include "ProcessErrorHandler.hpp"
#include <QDebug>
#include <QThread>

namespace Xeth{


ProcessErrorHandler::ProcessErrorHandler(ProcessSupervisor &process, size_t limit) : 
    _process(process),
    _limit(limit),
    _errors(0),
    _lastErrorTime(0)
{}


void ProcessErrorHandler::operator()()
{
    operator()("process failed: too many restarts");
}


void ProcessErrorHandler::operator()(const char *error)
{
    time_t now = time(NULL);
    if((now - _lastErrorTime) < 100)
    {
        if(++_errors > _limit)
        {
            qDebug()<<error;
            throw std::runtime_error(error);
        }
    }
    else
    {
        _errors = 0; //reseting error counter
    }

    _lastErrorTime =  now;
    qDebug()<<"restarting "<<_process.getProgram()<<" process";
    _process.restart();
}


}
