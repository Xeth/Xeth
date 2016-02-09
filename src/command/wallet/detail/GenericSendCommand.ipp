namespace Xeth{

template<class Sender, class Validator>
GenericSendCommand<Sender, Validator>::GenericSendCommand(Ethereum::Connector::Provider &provider, DataBase &database):
    _wallet(provider),
    _database(database)
{}


template<class Sender, class Validator>
QVariant GenericSendCommand<Sender, Validator>::operator()(const QVariantMap &request)
{
    QVariantMap result;

    std::string from = request["from"].toString().toStdString();
    std::string to = request["to"].toString().toStdString();
    std::string password = request["password"].toString().toStdString();

    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > dAmount(request["amount"].toDouble());
    dAmount *= 1000000000000000000;

    BigInt amount(dAmount.str(0, std::ios_base::fixed));

    Validator validator;

    if(!validator(to))
    {
        return QVariant::fromValue(false);
    }

    try
    {

        if(amount<=0 || _wallet.getBalance(from) < amount)
        {
            return QVariant::fromValue(false);
        }

        if(!_wallet.unlockAccount(from, password, 5))
        {
            //maybe it was a stealth payment
            StealthPaymentStore &payments = _database.getStealthPayments();
            StealthPaymentStore::Iterator it = payments.find(from.c_str());
            if(it==payments.end())
            {
                return QVariant::fromValue(false);
            }

            //address found, lets import key
            //finding stealth address
            StealthRedeemKeyFactory factory(_database);
            EthereumKey key = factory.create(*it, password);
            _database.getEthereumKeys().insert(key);
            if(!_wallet.unlockAccount(from, password, 5))
            {
                return QVariant::fromValue(false);
            }

        }

        Sender sender;
        std::string txid;
        if(request.contains("gas"))
        {
            BigInt gas(request["gas"].toString().toStdString());
            txid = sender(_wallet, _database, from, to, amount, gas);
        }
        else
        {
            txid = sender(_wallet, _database, from, to, amount);
        }
        return QVariant::fromValue(QString(txid.c_str()));
    }
    catch(...)
    {}
    return QVariant::fromValue(false);
}

}
