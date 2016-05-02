#include "ConfigFacade.hpp"


namespace Xeth{


ConfigFacade::ConfigFacade(DataBase &database, Invoker<Notifier> &invoker):
    _database(database),
    _invoker(invoker)
{}


QVariant ConfigFacade::get(const QString &name)
{
    GetConfigCommand command(_database);
    return _invoker.invoke(command, name);
}



QVariant ConfigFacade::set(const QVariantMap &request)
{
    AddConfigCommand command(_database);
    return _invoker.invoke(command, request);
}




}
