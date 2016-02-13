namespace Xeth{

template<class Store, class KeyGenerator, class CipherFactory>
GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::GenericGenerateKeyCommand(Store &store, Synchronizer &synchronizer) :
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store, class KeyGenerator, class CipherFactory>
QVariant GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::operator()(const QVariantMap &request)
{
    std::string address;
    if(!generate(request, address))
    {
        return QVariant::fromValue(false);
    }
    return QVariant::fromValue(QString(address.c_str()));
}


template<class Store, class KeyGenerator, class CipherFactory>
bool GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::generate(const QVariantMap &request, std::string &address)
{

    if(!request.contains("password"))
    {
        return false;
    }

    std::string password = request["password"].toString().toStdString();
    typename Store::Data key;
    
    try
    {
        if(request.contains("entropy"))
        {
            std::string entropy = request["entropy"].toString().toStdString();
            if(entropy.size()<32)
            {
                return false;
            }
            key = _keyGenerator.generate((const unsigned char *)entropy.data(), entropy.size(), _cipherFactory.create(), password);
        }
        else
        {
            key = _keyGenerator.generate(_cipherFactory.create(), password);
        }
    }
    catch(...)
    {
        return false;
    }

    if(!_store.insert(key))
    {
        return false;
    }

    _synchronizer.watch(key);
    AddressBuilder builder;
    address = builder.build(key);
    return true;
}


}
