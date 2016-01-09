#pragma once

#include <QVariant>
#include <QVariantMap>

#include "DataBase.hpp"


namespace Xeth{



class RemoveContactCommand
{
    public:
        RemoveContactCommand(DataBase &);

        QVariant operator()(const QString &);

    private:
        DataBase &_database;

};



}
