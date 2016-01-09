#pragma once

#include <QVariant>
#include <QVariantMap>

#include "DataBase.hpp"


namespace Xeth{



class GetConfigCommand
{
    public:
        GetConfigCommand(DataBase &);

        QVariant operator()(const QString &);

    private:
        DataBase &_database;

};


}
