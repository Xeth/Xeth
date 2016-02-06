#pragma once

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"


namespace Xeth{



class AddContactCommand
{
    public:
        AddContactCommand(DataBase &);

        QVariant operator()(const QVariantMap &);

    private:
        DataBase &_database;

};



}
