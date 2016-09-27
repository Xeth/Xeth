#pragma once

#include <QProcess>
#include "conf/Settings.hpp"
#include "IpfsProcessInitializer.hpp"
#include "GenericProcessFactory.hpp"


namespace Xeth{


class IpfsProcessFactory : public GenericProcessFactory<IpfsProcessInitializer>
{
    public:

//        static QProcess * Create(const Settings &);
//        static QProcess * Create();
        static QProcess * CreateDaemon(const Settings &);
        static QProcess * CreateDaemon();
};


}
