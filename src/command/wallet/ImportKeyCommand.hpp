#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "GenericImportKeyCommand.hpp"


namespace Xeth{


class ImportKeyCommand : public GenericImportKeyCommand<EthereumKeyStore>
{
    public:
        ImportKeyCommand(DataBase &);

};


}
