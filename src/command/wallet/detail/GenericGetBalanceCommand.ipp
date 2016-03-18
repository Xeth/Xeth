namespace Xeth{


template<BalanceType::Value type>
GenericGetBalanceCommand<type>::GenericGetBalanceCommand(Ethereum::Connector::Provider &provider) :
    _wallet(provider)
{}


template<BalanceType::Value type>
QVariant GenericGetBalanceCommand<type>::operator()(const char *address)
{
    Ethereum::Connector::BigInt balance = _wallet.getBalance(address, BalanceType::ToString(type));
    return balance.str().c_str();
}


template<BalanceType::Value type>
QVariant GenericGetBalanceCommand<type>::operator()(const QString &address)
{
    return operator ()(address.toStdString().c_str());
}


}
