#include "SendCommand.hpp"

namespace Xeth{


SendCommand::SendCommand(Ethereum::Connector::Provider &provider, DataBase &database) :
    _provider(provider),
    _database(database)
{}


QVariant SendCommand::operator()(const QVariantMap &request)
{
    qDebug()<<"send request : "<<request;
    QString to = request["address"].toString();
    QString from = request["from"].toString();
    QString password = request["password"].toString();
    QString amount = request["amount"].toString();
    const QVariant & gas = request["gas"];
    const QVariant & price = request["price"];

    bool strict = request.contains("checksum") ? request["checksum"].toBool() : false;
    size_t addrSize = to.length();

    if(addrSize==40||addrSize==42)
    {
        SendToAddressCommand command(_provider, _database);
        return send(command, from, to, password, amount, gas, price, request["logs"], strict);
    }
    SendToStealthCommand command(_provider, _database);
    return send(command, from, to, password, amount, gas, price, request["logs"], strict);

}


template<class Command>
QVariant SendCommand::send
(
    Command &command,
    const QString &from,
    const QString &to,
    const QString &password,
    const QString &amount,
    const QVariant &gas,
    const QVariant &price,
    const QVariant &logs,
    bool strict
)
{
    if(gas.isNull()||price.isNull())
    {
        return command(from, to, password, amount, logs, strict);
    }

    return command(from, to, password, amount, gas.toString(), price.toString(), logs, strict);
}




}
