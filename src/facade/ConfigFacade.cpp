#include "ConfigFacade.hpp"


namespace Xeth{


ConfigFacade::ConfigFacade(DataBase &database, Notifier &notifier):
    _database(database),
    _invoker(notifier)
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
