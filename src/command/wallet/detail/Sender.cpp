#include "Sender.hpp"

namespace Xeth{


std::string AddressSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    DataBase &database,
    const std::string &from,
    const std::string &to,
    const BigInt &amount
)
{
    std::string txid = wallet.sendTransaction(from, to, amount);
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, to, amount, time(NULL));
    return txid;
}


std::string AddressSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    DataBase &database,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const BigInt &gas
)
{
    std::string txid = wallet.sendTransaction(from, to, amount, gas);
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, to, amount, time(NULL));
    return txid;
}


std::string StealthSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    DataBase &database,
    const std::string &from,
    const std::string &to,
    const BigInt &amount
)
{
    Ethereum::PublicKeySerializer serializer;
    Ethereum::Stealth::Address address = Ethereum::Stealth::Address::FromString(to);
    Ethereum::Stealth::PaymentAddressBuilder builder(address);
    Ethereum::Stealth::PaymentAddress paymentAddr = builder.build();

    std::string data =  serializer.serialize(paymentAddr.getEphemPublicKey());
    std::string destination = paymentAddr.getAddresses()[0].toString();
    std::string txid = wallet.sendTransaction(from, destination, amount, data);
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, destination, address, amount, time(NULL));
    return txid;
}

std::string StealthSender::operator()
(
    Ethereum::Connector::Wallet &wallet,
    DataBase &database,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    const BigInt &gas
)
{

    Ethereum::PublicKeySerializer serializer;
    Ethereum::Stealth::Address address = Ethereum::Stealth::Address::FromString(to);
    Ethereum::Stealth::PaymentAddressBuilder builder(address);
    Ethereum::Stealth::PaymentAddress paymentAddr = builder.build();

    std::string data =  serializer.serialize(paymentAddr.getEphemPublicKey());
    std::string destination = paymentAddr.getAddresses()[0].toString();
    std::string txid = wallet.sendTransaction(from, destination, amount, data, gas);
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, destination, address, amount, time(NULL));
    return txid;
}


}
