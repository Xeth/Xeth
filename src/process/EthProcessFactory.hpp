#pragma once

#include <QProcess>
#include "conf/Settings.hpp"
#include "EthProcessInitializer.hpp"

namespace Xeth{

class EthProcessFactory
{
    public:

        static QProcess * Create(const Settings &);
        static QProcess * Create();
};


}
