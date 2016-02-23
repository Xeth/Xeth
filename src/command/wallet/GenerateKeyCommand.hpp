#pragma once 

#include <QVariant>
#include <QVariantMap>


#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"


#include "GenerateStealthKeyCommand.hpp"
#include "GenerateEthereumKeyCommand.hpp"



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



}
