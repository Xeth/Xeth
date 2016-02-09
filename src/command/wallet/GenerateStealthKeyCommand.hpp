#pragma once 

#include "detail/GenericGenerateKeyCommand.hpp"
#include "types/StealthKey.hpp"

namespace Xeth{


class GenerateStealthKeyCommand : 
    public GenericGenerateKeyCommand<StealthKeyStore, Ethereum::Stealth::KeyGenerator, CipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<StealthKeyStore, Ethereum::Stealth::KeyGenerator, CipherFactory> Base;

    public:
        GenerateStealthKeyCommand(DataBase &, Synchronizer &);

};


}
