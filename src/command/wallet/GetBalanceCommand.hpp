#pragma once

#include "detail/GenericGetBalanceCommand.hpp"

namespace Xeth{


typedef GenericGetBalanceCommand<BalanceType::latest> GetBalanceCommand;
typedef GenericGetBalanceCommand<BalanceType::pending> GetPendingBalanceCommand;

}
