#pragma once

#include <QVariant>
#include <QString>
#include <QVariantMap>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "ethrpc/transport/Path.hpp"

#include "Settings.hpp"


namespace Xeth{


class ExportKeyCommand
{
    public:
        ExportKeyCommand(const Settings &);

        QVariant operator()(const QVariantMap &path);


    private:
        const Settings &_settings;
};


}
