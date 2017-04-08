#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "database/StealthKeyStore.hpp"
#include "database/EthereumKeyStore.hpp"
#include "database/KeyAttributesReader.hpp"
#include "database/KeyImporter.hpp"

#include "synchronizer/Synchronizer.hpp"

#include "AddressBuilder.hpp"


namespace Xeth{


template<class Importer>
class GenericImportKeyCommand
{
    public:

        GenericImportKeyCommand(typename Importer::Store &, Synchronizer &);
        QVariant operator ()(const QVariantMap &request);

        bool import(const QVariantMap &request, QString &address);
        bool import(const QString &file, const QString &password, QString &address);

    private:
        Importer _importer;
        Synchronizer &_synchronizer;
};


}

#include "GenericImportKeyCommand.ipp"


