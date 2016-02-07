#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "detail/GenericImportKeyCommand.hpp"

#include "synchronizer/Synchronizer.hpp"

namespace Xeth{


class ImportKeyCommand : public GenericImportKeyCommand<EthereumKeyStore>
{
    public:
        typedef GenericImportKeyCommand<EthereumKeyStore> Base;

    public:
        ImportKeyCommand(DataBase &db, Synchronizer &);

};


}
