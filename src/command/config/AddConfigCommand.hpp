#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"


namespace Xeth{



class AddConfigCommand
{
    public:
        AddConfigCommand(DataBase &);

        QVariant operator()(const QVariantMap &);
        QVariant operator()(const QString &, const QString &);

    private:
        DataBase &_database;

};


}
