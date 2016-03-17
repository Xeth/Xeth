#include "ListTransactionsCommand.hpp"


namespace Xeth{


ListTransactionsCommand::ListTransactionsCommand(DataBase &database) :
    _database(database)
{}


QVariant ListTransactionsCommand::operator ()(const QVariantMap &request)
{
    QJsonArray result;

    TransactionStore & store = _database.getTransactions();

    if(request.contains("limit"))
    {
        DataRange<TransactionStore> range(store);
        range.setLimit(request["limit"].toInt());

        if(request.contains("offset"))
        {
            range.setOffset(request["offset"].toInt());
        }

        for(DataRange<TransactionStore>::ReverseIterator it = range.rbegin(), end = range.rend(); it!=end; ++it)
        {
            result.push_back(*it);
        }
    }
    else
    {
        for(TransactionStore::ReverseIterator  it = store.rbegin(), end = store.rend(); it!=end; ++it)
        {
            result.push_back(*it);
        }
    }

    return QVariant::fromValue(result.toVariantList());
}


}
