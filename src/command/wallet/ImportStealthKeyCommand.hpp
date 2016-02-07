#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "database/StealthKeyStore.hpp"
#include "database/KeyAttributesReader.hpp"

#include "detail/GenericImportKeyCommand.hpp"

namespace Xeth{


class ImportStealthKeyCommand : public GenericImportKeyCommand<StealthKeyStore>
{
    public:
        typedef GenericImportKeyCommand<StealthKeyStore> Base;

    public:
        ImportStealthKeyCommand(DataBase &db, Synchronizer &);

};


}
