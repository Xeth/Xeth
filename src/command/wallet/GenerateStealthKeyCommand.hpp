#pragma once 

#include "detail/GenericGenerateKeyCommand.hpp"
#include "types/StealthKey.hpp"

namespace Xeth{


class GenerateStealthKeyCommand : 
    public GenericGenerateKeyCommand<StealthKeyStore, StealthKeyGenerator, StealthKeyCipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<StealthKeyStore, StealthKeyGenerator, StealthKeyCipherFactory> Base;

    public:
        GenerateStealthKeyCommand(DataBase &, Synchronizer &);

};


}
