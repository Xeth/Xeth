#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"
#include "GenericImportKeyCommand.hpp"


namespace Xeth{


class ImportStealthKeyCommand : public GenericImportKeyCommand<StealthKeyStore>
{
    public:
        ImportStealthKeyCommand(DataBase &);

};


}
