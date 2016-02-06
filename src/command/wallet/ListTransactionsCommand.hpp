#pragma once

#include <QVariant>
#include <QString>
#include <QJsonArray>

#include "database/DataBase.hpp"
#include "database/DataRange.hpp"



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

