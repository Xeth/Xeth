#pragma once

#include "database/DataBase.hpp"
#include "detail/GenericExportKeyCommand.hpp"


namespace Xeth{


class ExportStealthKeyCommand : public GenericExportKeyCommand<StealthKeyStore>
{
    public:
        ExportStealthKeyCommand(const DataBase &);

};


}
