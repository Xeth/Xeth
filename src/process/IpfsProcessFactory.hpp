#pragma once

#include <QProcess>
#include "env/Settings.hpp"
#include "IpfsProcessInitializer.hpp"

namespace Xeth{

class IpfsProcessFactory
{
    public:

        static QProcess * Create(const Settings &);
        static QProcess * Create();
        static QProcess * CreateDaemon(const Settings &);
        static QProcess * CreateDaemon();
};


}
