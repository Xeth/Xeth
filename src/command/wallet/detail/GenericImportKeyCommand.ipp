namespace Xeth{


template<class Store, class Validator>
GenericImportKeyCommand<Store, Validator>::GenericImportKeyCommand(Store &store, Synchronizer &synchronizer) : 
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store, class Validator>
bool GenericImportKeyCommand<Store, Validator>::import(const QVariantMap &request, std::string &address)
{

    if(!request.contains("file")||!request.contains("password"))
    {
        return false;
    }

    std::string file = request["file"].toString().toStdString();

    if(!file.size())
    {
        return false;
    }

    typename Store::Data key;
    Json::Value json;

    FileImporter<Store, Validator> importer(_store, Validator(request["password"].toString().toStdString()));

    if(!importer.import(file, json, key))
    {
        return false;
    }

    KeyAttributesReader<Store> attr(file, json);
    _synchronizer.watch(key, attr.getCreationTime());
    AddressBuilder builder;
    address = builder.build(key);

    return true;
}


template<class Store, class Validator>
QVariant GenericImportKeyCommand<Store, Validator>::operator()(const QVariantMap &request)
{
    std::string address;
    if(!import(request, address))
    {
        return QVariant::fromValue(false);
    }
    return QVariant::fromValue(QString(address.c_str()));
}


}
