namespace Xeth{

template<class Sender, class Validator, class Estimator>
GenericSendCommand<Sender, Validator, Estimator>::GenericSendCommand(Ethereum::Connector::Provider &provider, DataBase &database):
    _wallet(provider),
    _database(database),
    _estimator(provider)
{}


template<class Sender, class Validator, class Estimator>
QVariant GenericSendCommand<Sender, Validator, Estimator>::operator()(const QVariantMap &request)
{

    if(!request.contains("from")||!request.contains("to")||!request.contains("amount")||!request.contains("password"))
    {
        return QVariant::fromValue(false);
    }

    bool strict = request.contains("checksum") ? request["checksum"].toBool() : true;

    if(request.contains("gas") && request.contains("price"))
    {
        _sender.setGasPrice(BigInt(request["price"].toString().toStdString()));
        _sender.setGasLimit(BigInt(request["gas"].toString().toStdString()));
    }
    else
    {
        _sender.unsetGasLimit();
        _sender.unsetGasPrice();
    }

    return send(request["from"].toString(), request["to"].toString(), request["password"].toString(), request["amount"].toString(), request["logs"], strict);

}

template<class Sender, class Validator, class Estimator>
QVariant GenericSendCommand<Sender, Validator, Estimator>::send
(
    const QString &from,
    const QString &to,
    const QString &password,
    const QString &amount,
    const QVariant &logs,
    bool strict
)
{

    return send(from.toStdString(), to.toStdString(), password.toStdString(), amount.toStdString(), logs, strict);
}


template<class Sender, class Validator, class Estimator>
QVariant GenericSendCommand<Sender, Validator, Estimator>::send
(
    const std::string &from,
    const std::string &to,
    const std::string &password,
    const std::string &amountStr,
    const QVariant &logs,
    bool strict
)
{

    if(!validateDestination(to, strict))
    {
        throw std::runtime_error("invalid address");
    }

    if(!unlockSender(from, password))
    {
        throw std::runtime_error("invalid password");
    }

    TransactionObjectBuilder builder;

    if(!logs.isNull())
    {
        builder.setExtraData(logs.toMap());
    }

    BigInt amount;

    if(amountStr=="all")
    {
        amount = _wallet.getBalance(from);
        BigInt gasPrice = _sender.hasGasPrice() ? _sender.getGasPrice() : _estimator.getGasPrice();
        BigInt gas = _sender.hasGas() ? _sender.getGas() : _estimator.estimate(from, to, amount);
        BigInt fee = gas * gasPrice;
        amount -= fee;
    }
    else
    {
        amount = BigInt(amountStr);
    }

    QString txid = _sender(_wallet, builder, from, to, amount).c_str();
    _database.getTransactions().insert(builder.build());

    return txid;
}


template<class Sender, class Validator, class Estimator>
QVariant GenericSendCommand<Sender, Validator, Estimator>::operator()
(
    const QString &from,
    const QString &to,
    const QString &password,
    const QString &amount,
    const QVariant &logs,
    bool strict
)
{
    _sender.unsetGasPrice();
    _sender.unsetGasLimit();
    return send(from, to, password, amount, logs, strict);
}


template<class Sender, class Validator, class Estimator>
QVariant GenericSendCommand<Sender, Validator, Estimator>::operator()
(
    const QString &from,
    const QString &to,
    const QString &password,
    const QString &amount,
    const QString &gas,
    const QString &price,
    const QVariant &logs,
    bool strict
)
{
    _sender.setGasPrice(BigInt(price.toStdString()));
    _sender.setGasLimit(BigInt(gas.toStdString()));

    return send(from, to, password, amount, logs, strict);

}


template<class Sender, class Validator, class Estimator>
bool GenericSendCommand<Sender, Validator, Estimator>::validateDestination(const std::string &to, bool strict)
{
    Validator validator;
    return validator(to, strict);
}


template<class Sender, class Validator, class Estimator>
bool GenericSendCommand<Sender, Validator, Estimator>::unlockSender(const std::string &from, const std::string &password)
{
    if(!_wallet.unlockAccount(from, password, 5))
    {
        //maybe it was a stealth payment
        StealthSpendKeyRedeemer redeemer(_database);
        if(!redeemer.redeem(from, password))
        {
            return false;
        }

        if(!_wallet.unlockAccount(from, password, 5))
        {
            return false;
        }
    }
    return true;
}



}
