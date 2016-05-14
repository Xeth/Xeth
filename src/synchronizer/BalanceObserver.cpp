#include "BalanceObserver.hpp"


namespace Xeth{


BalanceObserver::BalanceObserver(Ethereum::Connector::Provider &provider, time_t interval) :
    _interval(interval),
    _wallet(provider)
{
    qRegisterMetaType<BigInt>("BigInt");
    if(!QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(checkBalanceAsync())))
    {
        throw std::runtime_error("failed to connect timeout signal");
    }
}



void BalanceObserver::watch(const std::string &address)
{
    AccountInfo info;
    info.address = address;
    _accounts.push_back(info);
}


void BalanceObserver::start()
{
    _timer.start(_interval);
}


time_t BalanceObserver::getUpdateInterval() const
{
    return _interval;
}


void BalanceObserver::checkBalanceAsync()
{
    QtConcurrent::run(this, &BalanceObserver::checkBalance);
}


void BalanceObserver::checkBalance()
{
    size_t count = _accounts.count();

    //no need to lock
    for(size_t i=0; i < count; ++i)
    {
        checkBalance(_accounts[i]);
    }
    _timer.start(_interval);
}


void BalanceObserver::checkBalance(AccountInfo &info)
{
    BigInt confirmed = _wallet.getBalance(info.address);
    BigInt unconfirmed = _wallet.getBalance(info.address.c_str(), "pending");
    if(confirmed != info.confirmed || unconfirmed != info.unconfirmed)
    {
        info.confirmed = confirmed;
        info.unconfirmed = unconfirmed;
        emit Update(QString(info.address.c_str()), unconfirmed, confirmed);
    }
}



}
