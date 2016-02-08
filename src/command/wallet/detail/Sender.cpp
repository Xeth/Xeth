#include "Sender.hpp"

namespace Xeth{


std::string AddressSender::operator()(Ethereum::Connector::Wallet &wallet, const std::string &from, const std::string &to, const BigInt &amount)
{
    return wallet.sendTransaction(from, to, amount);
}


std::string StealthSender::operator()(Ethereum::Connector::Wallet &wallet, const std::string &from, const std::string &to, const BigInt &amount)
{
    StealthAddress address = Literal<StealthAddress>(to);
    StealthPaymentAddressBuilder builder(address);
    StealthPaymentAddress paymentAddr = builder.build();
    return wallet.sendTransaction(from, paymentAddr.getAddresses()[0].toString(), amount, Literal(paymentAddr.getEphemPublicKey()));
}


}
