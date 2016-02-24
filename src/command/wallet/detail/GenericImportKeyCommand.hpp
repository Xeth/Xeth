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

    private:
        bool import(const QVariantMap &request, std::string &address);

    private:
        Store &_store;
        Synchronizer &_synchronizer;
};


}

#include "GenericImportKeyCommand.ipp"


