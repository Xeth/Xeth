#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QJsonArray>

#include "database/DataBase.hpp"


namespace Xeth{



class ListContactsCommand
{
    public:
        ListContactsCommand(DataBase &);

        QVariant operator()();

    private:
        DataBase &_database;

};



}
