#pragma once

#include <QProcess>
#include <QProcessEnvironment>

#include "conf/Settings.hpp"


namespace Xeth{


template<class ProcessInitializer>
class GenericProcessFactory
{
    public:
        static QProcess * Create(const Settings &);
        static QProcess * Create();
};


}


#include "GenericProcessFactory.ipp"
