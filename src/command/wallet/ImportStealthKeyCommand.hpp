#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "database/StealthKeyStore.hpp"
#include "database/KeyAttributesReader.hpp"

#include "detail/GenericImportKeyCommand.hpp"
#include "detail/StealthKeyValidator.hpp"

namespace Xeth{


class ImportStealthKeyCommand : public GenericImportKeyCommand<StealthKeyStore, StealthKeyValidator>
{
    public:
        typedef GenericImportKeyCommand<StealthKeyStore, StealthKeyValidator> Base;

    public:
        ImportStealthKeyCommand(DataBase &db, Synchronizer &);

};


}
