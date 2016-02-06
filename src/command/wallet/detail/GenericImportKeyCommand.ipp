namespace Xeth{


template<class Store>
GenericImportKeyCommand<Store>::GenericImportKeyCommand(Store &store) : 
    _store(store)
{}


template<class Store>
QVariant GenericImportKeyCommand<Store>::operator()(const QVariantMap &request)
{
    QString file = request["file"].toString();

    if(!file.length())
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(_store.importFile(file.toStdString().c_str()));
}


}
