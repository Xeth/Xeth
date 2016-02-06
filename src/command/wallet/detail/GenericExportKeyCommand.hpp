#pragma once 

#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QDir>
#include <QFile>


namespace Xeth{


template<class Store>
class GenericExportKeyCommand
{
    public:
        GenericExportKeyCommand(const Store &);
        QVariant operator()(const QVariantMap &);

    private:
        const Store &_store;

};


}

#include "GenericExportKeyCommand.ipp"
