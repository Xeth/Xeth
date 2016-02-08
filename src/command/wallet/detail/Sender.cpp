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
    StealthAddress address = Literal<StealthAddress>(to);
    StealthPaymentAddressBuilder builder(address);
    StealthPaymentAddress paymentAddr = builder.build();
    std::string txid = wallet.sendTransaction(from, paymentAddr.getAddresses()[0].toString(), amount, Literal(paymentAddr.getEphemPublicKey()));
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, to, address, amount, time(NULL));
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
    StealthAddress address = Literal<StealthAddress>(to);
    StealthPaymentAddressBuilder builder(address);
    StealthPaymentAddress paymentAddr = builder.build();
    std::string txid = wallet.sendTransaction(from, paymentAddr.getAddresses()[0].toString(), amount, Literal(paymentAddr.getEphemPublicKey()), gas);
    database.getTransactions().insert(TransactionCategory::Sent, txid, from, to, address, amount, time(NULL));
    return txid;
}


}
