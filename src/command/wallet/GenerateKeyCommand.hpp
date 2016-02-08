#pragma once 

#include "detail/GenericGenerateKeyCommand.hpp"


namespace Xeth{


class GenerateKeyCommand : 
    public GenericGenerateKeyCommand<EthereumKeyStore, EthereumKeyGenerator, EthereumKeyCipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<EthereumKeyStore, EthereumKeyGenerator, EthereumKeyCipherFactory> Base;

    public:
        GenerateKeyCommand(DataBase &, Synchronizer &);

};


}
