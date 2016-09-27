#pragma once

#include <QProcess>
#include "conf/Settings.hpp"
#include "EthProcessInitializer.hpp"
#include "GenericProcessFactory.hpp"

namespace Xeth{

typedef GenericProcessFactory<EthProcessInitializer> EthProcessFactory;


}
