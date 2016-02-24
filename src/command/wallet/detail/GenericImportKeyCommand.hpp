#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "database/StealthKeyStore.hpp"
#include "database/EthereumKeyStore.hpp"
#include "database/KeyAttributesReader.hpp"

#include "synchronizer/Synchronizer.hpp"

#include "AddressBuilder.hpp"


namespace Xeth{


template<class Store, class Validator>
class GenericImportKeyCommand
{
    public:
        GenericImportKeyCommand(Store &, Synchronizer &);

        QVariant operator ()(const QVariantMap &request);

        bool import(const QVariantMap &request, QString &address);
        bool import(const QString &file, const QString &password, QString &address);

    private:
        Store &_store;
        Synchronizer &_synchronizer;
};


}

#include "GenericImportKeyCommand.ipp"


