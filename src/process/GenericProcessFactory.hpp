#pragma once

#include <QProcess>
#include <QProcessEnvironment>
#include <QStringList>

#include "conf/Settings.hpp"


namespace Xeth{


template<class ProcessInitializer>
class GenericProcessFactory
{
    public:
        static QProcess * Create(const Settings &);
        static QProcess * Create(const Settings &, const QStringList &args);
        static QProcess * Create();
};


}


#include "GenericProcessFactory.ipp"
