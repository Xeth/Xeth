#pragma once

#include <QVariant>
#include <QString>
#include <QVariantMap>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <boost/filesystem.hpp>

#include "ethrpc/transport/Path.hpp"

#include "database/DataBase.hpp"

namespace Xeth{


class ExportKeyCommand
{
    public:
        ExportKeyCommand(const DataBase &);

        QVariant operator()(const QVariantMap &path);


    private:
        const DataBase &_database;
};


}
