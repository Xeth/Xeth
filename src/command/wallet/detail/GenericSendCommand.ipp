namespace Xeth{

template<class Sender, class Validator>
GenericSendCommand<Sender, Validator>::GenericSendCommand(Ethereum::Connector::Provider &provider):
    _wallet(provider)
{}


template<class Sender, class Validator>
QVariant GenericSendCommand<Sender, Validator>::operator()(const QVariantMap &request)
{
    QVariantMap result;
    QVariantMap error;

    std::string from = request["from"].toString().toStdString();
    std::string to = request["to"].toString().toStdString();
    std::string password = request["password"].toString().toStdString();

    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > dAmount(request["amount"].toDouble());
    dAmount *= 1000000000000000000;

    BigInt amount(dAmount.str(0, std::ios_base::fixed));

    Validator validator;

    if(!validator(to))
    {
        error["address"] = true;
    }

    if(amount<=0 || _wallet.getBalance(from) < amount)
    {
        error["amount"] = true;
    }

    if(!_wallet.unlockAccount(from, password, 5))
    {
        error["password"] = true;
    }

    if(!error.empty())
    {
        result["error"] = error;
    }
    else
    {
        Sender sender;
        std::string txid = sender(_wallet, from, to, amount);
        result["txid"] = txid.c_str();
    }

    return result;
}

}
