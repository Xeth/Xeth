namespace Xeth{


template<class Store>
GenericImportKeyCommand<Store>::GenericImportKeyCommand(Store &store, Synchronizer &synchronizer) : 
    _store(store),
    _synchronizer(synchronizer)
{}


template<class Store>
bool GenericImportKeyCommand<Store>::import(const QVariantMap &request)
{

    std::string file = request["file"].toString().toStdString();

    if(!file.size())
    {
        return false;
    }

    typename Store::Data key;
    Json::Value json;

    FileImporter<Store> importer(_store);

    if(!importer.import(file, json, key))
    {
        return false;
    }

    KeyAttributesReader<Store> attr(file, json);
    _synchronizer.watch(key, attr.getCreationTime());
    return true;
}


template<class Store>
QVariant GenericImportKeyCommand<Store>::operator()(const QVariantMap &request)
{
    return QVariant::fromValue(import(request));
}


}
