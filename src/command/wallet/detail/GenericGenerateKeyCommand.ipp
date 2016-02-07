namespace Xeth{

template<class Store, class KeyGenerator, class CipherParamsGenerator>
GenericGenerateKeyCommand<Store, KeyGenerator, CipherParamsGenerator>::GenericGenerateKeyCommand(Store &store, Synchronizer &synchronizer) :
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store, class KeyGenerator, class CipherParamsGenerator>
QVariant GenericGenerateKeyCommand<Store, KeyGenerator, CipherParamsGenerator>::operator()(const QVariantMap &request)
{
    return QVariant::fromValue(generate(request));
}


template<class Store, class KeyGenerator, class CipherParamsGenerator>
bool GenericGenerateKeyCommand<Store, KeyGenerator, CipherParamsGenerator>::generate(const QVariantMap &request)
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
            key = _keyGenerator.generate(entropy.data(), entropy.size(), _paramsGenerator.generate(), password);
        }
        else
        {
            key = _keyGenerator.generate(_paramsGenerator.generate(), password);
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
