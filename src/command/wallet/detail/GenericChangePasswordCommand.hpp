#pragma once 

#include <QVariant>
#include <QVariantMap>


namespace Xeth{


template<class Store, class ChangePasswordOperation>
class GenericChangePasswordCommand
{
    public:
        GenericChangePasswordCommand(Store &);

        QVariant operator()(const QVariantMap &);
        bool execute(const QString &address, const QString &password, const QString &newPassword);

    private:
        Store &_store;

};


}

#include "GenericChangePasswordCommand.ipp"
