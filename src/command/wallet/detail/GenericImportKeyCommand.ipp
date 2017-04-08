namespace Xeth{


template<class Importer>
GenericImportKeyCommand<Importer>::GenericImportKeyCommand(typename Importer::Store &store, Synchronizer &synchronizer) : 
    _importer(store),
    _synchronizer(synchronizer)
{}


template<class Importer>
bool GenericImportKeyCommand<Importer>::import(const QString &file, const QString &password, QString &address)
{

    typename Importer::Data key;
    Json::Value json;

    std::string path = file.toStdString();

    if(!_importer.import(path.c_str(), json, key, password))
    {
        return false;
    }

    KeyAttributesReader<typename Importer::Store> attr(path, json);
    _synchronizer.watch(key, attr.getCreationTime());
    AddressBuilder builder;
    address = builder.build(key).c_str();
    return true;
}

template<class Importer>
bool GenericImportKeyCommand<Importer>::import(const QVariantMap &request, QString &address)
{

    if(!request.contains("file")||!request.contains("password"))
    {
        return false;
    }

    return import(request["file"].toString(), request["password"].toString(), address);
}


template<class Importer>
QVariant GenericImportKeyCommand<Importer>::operator()(const QVariantMap &request)
{
    QString address;
    if(!import(request, address))
    {
        return QVariant::fromValue(false);
    }
    return QVariant::fromValue(address);
}


}
