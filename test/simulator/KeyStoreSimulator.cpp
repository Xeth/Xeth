#include "KeyStoreSimulator.hpp"

KeyStoreSimulator::KeyStoreSimulator(Xeth::DataBase &)
{}

std::vector<std::string> KeyStoreSimulator::getAccounts()
{
    std::vector<std::string> result;
    for(std::map<std::string,std::string>::iterator it=_accounts.begin(), end=_accounts.end(); it!=end; ++it)
    {
        result.push_back(it->first);
    }
    return result;
}


void KeyStoreSimulator::lockAccount(const char *address)
{
    _locks[address] = 0;
}


void KeyStoreSimulator::registerAccount(const char *address, const char *password)
{
    _accounts[address] = password;
}


bool KeyStoreSimulator::unlockAccount(const char *address, const char *password, size_t duration)
{
    if(_accounts[address] == password)
    {
        _locks[address] = time(NULL) + duration;
        return true;
    }
    return false;
}


bool KeyStoreSimulator::isUnlocked(const char *address)
{
    std::map<std::string, time_t>::iterator it = _locks.find(address);
    if(it==_locks.end())
    {
        return false;
    }
    if(it->second < time(NULL))
    {
        return false;
    }
    return true;
}
