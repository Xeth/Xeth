#include "GetBalanceCommand.hpp"



namespace Xeth{


GetBalanceCommand::GetBalanceCommand(Ethereum::Connector::Provider &provider) :
    _wallet(provider)
{}


QVariant GetBalanceCommand::operator()(const char *address)
{
    Ethereum::Connector::BigInt balance = _wallet.getBalance(address);
    return balance.str().c_str();
}


QVariant GetBalanceCommand::operator()(const QString &address)
{
    return operator ()(address.toStdString().c_str());
}


}
