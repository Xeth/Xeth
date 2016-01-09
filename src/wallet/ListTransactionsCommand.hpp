#pragma once

#include <QVariant>
#include <QString>
#include <QJsonArray>

#include "DataBase.hpp"
#include "database/StoreRange.hpp"



namespace Xeth{



class ListTransactionsCommand
{
    public:
        ListTransactionsCommand(DataBase &);

        QVariant operator()(const QVariantMap &);

    private:
        DataBase &_database;

};


}

