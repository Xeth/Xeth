#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "detail/GenericImportKeyCommand.hpp"


namespace Xeth{


class ImportKeyCommand : public GenericImportKeyCommand<EthereumKeyStore>
{
    public:
        ImportKeyCommand(DataBase &);

};


}
