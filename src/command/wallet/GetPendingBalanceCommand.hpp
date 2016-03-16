#pragma once

#include "detail/GenericGetBalanceCommand.hpp"

namespace Xeth{


typedef GenericGetBalanceCommand<BalanceType::pending> GetBalanceCommand;


}
