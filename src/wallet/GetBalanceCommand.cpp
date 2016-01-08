#include "GetBalanceCommand.hpp"



namespace Xeth{


GetBalanceCommand::GetBalanceCommand(Ethereum::Connector::Provider &provider) :
    _wallet(provider)
{}


QVariant GetBalanceCommand::operator()(const char *address)
{
    Ethereum::Connector::BigInt amount = _wallet.getBalance(address);
    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > balance(amount);
    balance /= 1000000000000000000;
    return balance.str().c_str();
}


QVariant GetBalanceCommand::operator()(const QString &address)
{
    return operator ()((const char *)address.data());
}


}
