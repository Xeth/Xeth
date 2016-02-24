namespace Xeth{


template<class Store, class Validator>
GenericImportKeyCommand<Store, Validator>::GenericImportKeyCommand(Store &store, Synchronizer &synchronizer) : 
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store, class Validator>
bool GenericImportKeyCommand<Store, Validator>::import(const QString &file, const QString &password, QString &address)
{

    typename Store::Data key;
    Json::Value json;

    FileImporter<Store, Validator> importer(_store, Validator(password.toStdString()));

    std::string path = file.toStdString();

    if(!importer.import(path.c_str(), json, key))
    {
        return false;
    }

    KeyAttributesReader<Store> attr(path, json);
    _synchronizer.watch(key, attr.getCreationTime());
    AddressBuilder builder;
    address = builder.build(key).c_str();
    return true;
}

template<class Store, class Validator>
bool GenericImportKeyCommand<Store, Validator>::import(const QVariantMap &request, QString &address)
{

    if(!request.contains("file")||!request.contains("password"))
    {
        return false;
    }

    return import(request["file"].toString(), request["password"].toString(), address);
}


template<class Store, class Validator>
QVariant GenericImportKeyCommand<Store, Validator>::operator()(const QVariantMap &request)
{
    QString address;
    if(!import(request, address))
    {
        return QVariant::fromValue(false);
    }
    return QVariant::fromValue(address);
}


}
