#include "SendToAddressCommand.hpp"

namespace Xeth{


SendToAddressCommand::SendToAddressCommand(Ethereum::Connector::Provider &provider):
    _wallet(provider)
{}


QVariant SendToAddressCommand::operator () (const QVariantMap &request)
{
    QVariantMap result;
    QVariantMap error;

    QString from = request["from"].toString();
    QString to = request["to"].toString();
    QString password = request["password"].toString();

    boost::multiprecision::number<boost::multiprecision::cpp_dec_float<12> > dAmount(request["amount"].toDouble());
    dAmount *= 1000000000000000000;

    BigInt amount(dAmount.str(0, std::ios_base::fixed));


    if(!_validator.validateAddress(to)||!_validator.validateAddress(from))
    {
        error["address"] = true;
    }

    if(amount<=0 || _wallet.getBalance((const char *)from.data()) < amount)
    {
        error["amount"] = true;
    }

    if(!_wallet.unlockAccount((const char *)from.data(), (const char *)password.data(), 5))
    {
        error["password"] = true;
    }

    if(!error.empty())
    {
        result["error"] = error;
    }
    else
    {
        std::string txid = _wallet.sendTransaction((const char *)from.data(), (const char *)to.data(), amount);
        result["txid"] = txid.c_str();
    }

    return result;

}

}

