#pragma once 

#include <QVariant>
#include <QVariantMap>

namespace Xeth{


template<class Store>
class GenericImportKeyCommand
{
    public:
        GenericImportKeyCommand(Store &);
        QVariant operator ()(const QVariantMap &request);

    private:
        Store &_store;
};


}

#include "GenericImportKeyCommand.ipp"


