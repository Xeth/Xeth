namespace Xeth{


template<class Store>
GenericExportKeyCommand<Store>::GenericExportKeyCommand(const Store &store) :
    _store(store)
{}


template<class Store>
QVariant GenericExportKeyCommand<Store>::operator()(const QVariantMap &request)
{
    QString address = request["address"].toString();
    QString destinationPath = request["destination"].toString();

    if(!address.length() || !destinationPath.length())
    {
        return QVariant::fromValue(false);
    }

    EthereumKeyStore::Iterator it = _store.find(address.toStdString().c_str());

    if(it==_store.end())
    {
        return QVariant::fromValue(false);
    }

    const boost::filesystem::path & path = it.path();
    QString destinationFile = destinationPath;
    destinationFile +=  QDir::separator();
    destinationFile += path.filename().c_str();
    return QVariant::fromValue(QFile::copy(path.string().c_str(), destinationFile));
}


}
