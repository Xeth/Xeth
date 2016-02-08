#pragma once

#include "detail/AddressValidator.hpp"
#include "detail/Sender.hpp"
#include "detail/GenericSendCommand.hpp"
#include "types/StealthKey.hpp"

namespace Xeth{


typedef GenericSendCommand<StealthSender, StealthAddressValidator> SendToStealthCommand;



}
