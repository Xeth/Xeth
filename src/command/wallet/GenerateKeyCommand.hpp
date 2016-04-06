#pragma once 

#include <QVariant>
#include <QVariantMap>


#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "detail/GenericGenerateKeyCommand.hpp"
#include "types/StealthKey.hpp"


namespace Xeth{



class GenerateKeyCommand
{
    public:

        GenerateKeyCommand(DataBase &, Synchronizer &);
        QVariant operator()(const QVariantMap &request);


    private:
        QVariant generateEthereumKey(const QVariantMap &);
        QVariant generateStealthKey(const QVariantMap &);


    private:
        DataBase &_database;
        Synchronizer &_synchronizer;
};


class GenerateEthereumKeyCommand : 
    public GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<EthereumKeyStore, Ethereum::KeyGenerator, CipherFactory> Base;

    public:
        GenerateEthereumKeyCommand(DataBase &, Synchronizer &);

};


class GenerateStealthKeyCommand : 
    public GenericGenerateKeyCommand<StealthKeyStore, Ethereum::Stealth::KeyGenerator, CipherFactory>
{
    public:
        typedef GenericGenerateKeyCommand<StealthKeyStore, Ethereum::Stealth::KeyGenerator, CipherFactory> Base;

    public:
        GenerateStealthKeyCommand(DataBase &, Synchronizer &);

};



}
