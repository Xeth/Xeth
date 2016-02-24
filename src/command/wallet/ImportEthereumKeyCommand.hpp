#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "detail/EthereumKeyValidator.hpp"
#include "detail/GenericImportKeyCommand.hpp"

#include "synchronizer/Synchronizer.hpp"

namespace Xeth{


class ImportEthereumKeyCommand : public GenericImportKeyCommand<EthereumKeyStore, EthereumKeyValidator>
{
    public:
        typedef GenericImportKeyCommand<EthereumKeyStore, EthereumKeyValidator> Base;

    public:
        ImportEthereumKeyCommand(DataBase &db, Synchronizer &);

};


}
