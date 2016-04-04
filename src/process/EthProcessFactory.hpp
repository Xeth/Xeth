#pragma once

#include <QProcess>
#include "env/Settings.hpp"
#include "EthProcessInitializer.hpp"

namespace Xeth{

class EthProcessFactory
{
    public:

        static QProcess * Create(const Settings &);
        static QProcess * Create();
};


}
