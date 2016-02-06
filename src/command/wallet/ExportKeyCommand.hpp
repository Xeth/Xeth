#pragma once

#include "database/DataBase.hpp"
#include "GenericExportKeyCommand.hpp"


namespace Xeth{


class ExportKeyCommand : public GenericExportKeyCommand<EthereumKeyStore>
{
    public:
        ExportKeyCommand(const DataBase &);

};


}
