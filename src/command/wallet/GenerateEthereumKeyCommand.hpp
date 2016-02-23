#pragma once 

#include "detail/GenericGenerateKeyCommand.hpp"


namespace Xeth{


class GenerateEthereumKeyCommand : 
    public GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory> Base;

    public:
        GenerateEthereumKeyCommand(DataBase &, Synchronizer &);

};


}
