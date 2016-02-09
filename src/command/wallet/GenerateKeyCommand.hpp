#pragma once 

#include "detail/GenericGenerateKeyCommand.hpp"


namespace Xeth{


class GenerateKeyCommand : 
    public GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory> Base;

    public:
        GenerateKeyCommand(DataBase &, Synchronizer &);

};


}
