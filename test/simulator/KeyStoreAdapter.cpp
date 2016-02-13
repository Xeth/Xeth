#include "KeyStoreAdapter.hpp"


KeyStoreAdapter::KeyStoreAdapter(Xeth::DataBase &database) :
    _store(database.getEthereumKeys())
{}


std::string KeyStoreAdapter::registerAccount(const std::string &password)
{
    Ethereum::KeyGenerator generator;
    Xeth::CipherFactory cipherFactory;
    Xeth::EthereumKey key = generator.generate(cipherFactory.create(), password);
    if(!_store.insert(key))
    {
        throw std::runtime_error("failed to register key");
    }

    return key.getAddress().toString();
}


bool KeyStoreAdapter::unlockAccount(const char *address, const char *password, size_t duration)
{
    try
    {
        Xeth::EthereumKey key = _store.get(address);
        key.getPrivateKey().unlock(password); //should throw if failed
        _locks[address] = time(NULL) + duration;
        return true;
    }
    catch(...)
    {}
    return false;
}


std::vector<std::string> KeyStoreAdapter::getAccounts()
{
    std::vector<std::string> result;
    for(Xeth::EthereumKeyStore::Iterator it = _store.begin(), end=_store.end(); it!=end; ++it)
    {
        result.push_back(it->getAddress().toString());
    }
    return result;
}


bool KeyStoreAdapter::isUnlocked(const char *address)
{
    return (_locks[address] > time(NULL));
}
