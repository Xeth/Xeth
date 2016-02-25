#pragma once

#include "database/DataBase.hpp"
#include "detail/GenericExportKeyCommand.hpp"


namespace Xeth{


class ExportEthereumKeyCommand : public GenericExportKeyCommand<EthereumKeyStore>
{
    public:
        ExportEthereumKeyCommand(const DataBase &);

};


}
