
#include "database/DataBase.hpp"
#include "Settings.hpp"

#include <QDebug>

QDebug operator<<(QDebug out, const std::string& str)
{
    out << QString::fromStdString(str);
    return out;
}

template<class Table>
void printDB(const Table &tbl)
{
    for(typename Table::Iterator it=tbl.begin(), end=tbl.end(); it!=end; ++it)
    {
        qDebug()<<it.keyString()<<":"<<*it;
    }
}


int main(int argc, char **argv)
{
    Xeth::Settings settings;
    settings.readCommandLineArgs(argc, argv);

    if(!settings.has("name"))
    {
        qDebug()<<"usage : dumpdb --name=database_to_dump [--testnet]";
        return 1;
    }

    Xeth::DataBase database(settings);

    QString name = settings.get("name");

    if(name=="transactions")
    {
        printDB(database.getTransactions());
    }
    else
    if(name=="stealthpayments")
    {
        printDB(database.getStealthPayments());
    }
    else
    if(name=="addressbook")
    {
        printDB(database.getAddressBook());
    }
    else
    if(name=="config")
    {
        printDB(database.getConfig());
    }
    else
    if(name=="scanindex")
    {
        printDB(database.getScanIndex());
    }
    else
    {
        qDebug()<<"invalid database name, available options(transactions, stealthpayments, addressbook, config, scanindex)";
        return 1;
    }

    return 0;
}
