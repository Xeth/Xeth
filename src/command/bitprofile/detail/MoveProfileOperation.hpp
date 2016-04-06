#pragma once 

#include "bitprofile/Registrar.hpp"
#include "types/BigInt.hpp"
#include "database/BitProfileStore.hpp"
#include "ProfileOperation.hpp"


namespace Xeth{


class MoveProfileOperation : public ProfileOperation
{
    public:
        MoveProfileOperation
        (
            BitProfileStore &store,
            const BitProfile::ProfileAdministrator &,
            const BitProfile::Registrar &,
            const QString &name,
            const QString &password,
            const BigInt &gas,
            Notifier &
        );

    protected:
        void execute();

    private:
        BitProfileStore &_store;
        BitProfile::Registrar _registrar;
        QString _name;
        BigInt _gas;
};


}
