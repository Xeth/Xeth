#pragma once

#include <QString>
#include <QVariant>

#include "DataBase.hpp"


namespace Xeth{



class GetTransactionCommand
{
    public:
        GetTransactionCommand(DataBase &);

        QVariant operator()(const QString &);
        QVariant operator()(const char *);

    private:
        DataBase &_database;
};



}
