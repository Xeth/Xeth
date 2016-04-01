#include "Sender.hpp"

namespace Xeth{


void Sender::setGasLimit(const BigInt &gas)
{
    _gas = gas;
}

void Sender::setGasPrice(const BigInt &price)
{
    _price = price;
}


std::string Sender::send
(
    Ethereum::Connector::Wallet &wallet,
    TransactionObjectBuilder &builder,
    const std::string &from,
    const std::string &to,
    const BigInt &amount
)
{
    std::string txid = (_gas>0 && _price>0) ? wallet.sendTransaction(from, to, amount) :  wallet.sendTransaction(from, to, amount, _gas, _price);
    builder.setDetails(txid, TransactionCategory::Sent, from, to, amount, time(NULL));
    return txid;
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
    return send(wallet, builder, from, to, amount);
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
    return send(wallet, txBuilder, from, destination, amount);
}



}
