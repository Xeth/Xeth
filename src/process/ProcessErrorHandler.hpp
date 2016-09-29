#pragma once 

#include "ProcessSupervisor.hpp"


namespace Xeth{


class ProcessErrorHandler
{
    public:
        ProcessErrorHandler(ProcessSupervisor &process, size_t limit);

        void operator()();
        void operator()(const char *error);

    private:
        ProcessSupervisor &_process;
        size_t _limit;
        size_t _errors;
        time_t _lastErrorTime;
};


}
