namespace Xeth{

template<class Store, class KeyGenerator, class CipherFactory>
GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::GenericGenerateKeyCommand(Store &store, Synchronizer &synchronizer) :
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store, class KeyGenerator, class CipherFactory>
QVariant GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::operator()(const QVariantMap &request)
{
    return QVariant::fromValue(generate(request));
}


template<class Store, class KeyGenerator, class CipherFactory>
bool GenericGenerateKeyCommand<Store, KeyGenerator, CipherFactory>::generate(const QVariantMap &request)
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
    return true;
}


}
