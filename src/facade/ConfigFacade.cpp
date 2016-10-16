#include "ConfigFacade.hpp"


namespace Xeth{


ConfigFacade::ConfigFacade(DataBase &database, Invoker<Notifier> &invoker):
    _database(database),
    _invoker(invoker)
{
    QObject::connect(&database.getConfig(), &ConfigStore::Change, this, &ConfigFacade::emitChange);
}


void ConfigFacade::emitChange(const QString &name, const QString &value)
{
    emit Change(name, value);
}


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
