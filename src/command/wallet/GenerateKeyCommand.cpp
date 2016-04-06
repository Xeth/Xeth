#include "GenerateKeyCommand.hpp"


namespace Xeth{


GenerateKeyCommand::GenerateKeyCommand(DataBase &database, Synchronizer &synchronizer) :
    _database(database),
    _synchronizer(synchronizer)
{}


QVariant GenerateKeyCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("type"))
    {
        return generateEthereumKey(request);
    }


    QString type = request["type"].toString();

    if(type=="stealth")
    {
        return generateStealthKey(request);
    }
    else
    if(type=="ethereum")
    {
        return generateEthereumKey(request);
    }
    else
    {
        return QVariant::fromValue(false);
    }

}


QVariant GenerateKeyCommand::generateEthereumKey(const QVariantMap &request)
{
    GenerateEthereumKeyCommand command(_database, _synchronizer);
    return command(request);
}


QVariant GenerateKeyCommand::generateStealthKey(const QVariantMap &request)
{
    GenerateStealthKeyCommand command(_database, _synchronizer);
    return command(request);
}


GenerateStealthKeyCommand::GenerateStealthKeyCommand(DataBase &database, Synchronizer &synchronizer):
    Base(database.getStealthKeys(), synchronizer)
{}


GenerateEthereumKeyCommand::GenerateEthereumKeyCommand(DataBase &database, Synchronizer &synchronizer):
    Base(database.getEthereumKeys(), synchronizer)
{}



}
