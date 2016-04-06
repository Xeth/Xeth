#include "Sender.hpp"

namespace Xeth{

Sender::Sender() :
    _hasGas(false),
    _hasGasPrice(false)
{}

void Sender::setGasLimit(const BigInt &gas)
{
    _gas = gas;
    _hasGas = true;
}

void Sender::setGasPrice(const BigInt &price)
{
    _price = price;
    _hasGasPrice = true;
}


void Sender::unsetGasPrice()
{
    _hasGasPrice = false;
}


void Sender::unsetGasLimit()
{
    _hasGas = false;
}

BigInt Sender::getGas()
{
    return _gas;
}


BigInt Sender::getGasPrice()
{
    return _price;
}

bool Sender::hasGasPrice()
{
    return _hasGasPrice;
}


bool Sender::hasGas()
{
    return _hasGas;
}

std::string Sender::send
(
    Ethereum::Connector::Wallet &wallet,
    TransactionObjectBuilder &builder,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const std::string &data
)
{
    std::string txid = send(wallet, from, to, amount, data);
    builder.setDetails(txid, TransactionCategory::Sent, from, to, amount, time(NULL));
    return txid;
}


std::string Sender::send
(
    Ethereum::Connector::Wallet &wallet,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const std::string &data
)
{
    if(_hasGas)
    {
        if(_hasGasPrice)
        {
            return wallet.sendTransaction(from, to, amount, data, _gas, _price);
        }
        else
        {
            return wallet.sendTransaction(from, to, amount, data, _gas);
        }
    }
    else
    {
        return wallet.sendTransaction(from, to, amount, data);
    }
}

std::string AddressSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    TransactionObjectBuilder &builder,
    const std::string &from,
    const std::string &to,
    const BigInt &amount
)
{
    return send(wallet, builder, from, to, amount, "");
}


std::string StealthSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    TransactionObjectBuilder &txBuilder,
    const std::string &from,
    const std::string &to,
    const BigInt &amount
)
{
    Ethereum::PublicKeySerializer serializer;
    Ethereum::Stealth::Address address = Ethereum::Stealth::Address::FromString(to);
    Ethereum::Stealth::PaymentAddressBuilder addrBuilder(address);
    Ethereum::Stealth::PaymentAddress paymentAddr = addrBuilder.build();

    std::string data =  serializer.serialize(paymentAddr.getEphemPublicKey());
    std::string destination = paymentAddr.getAddresses()[0].toString();

    txBuilder.setStealth(address);
    return send(wallet, txBuilder, from, destination, amount, data);
}



}
