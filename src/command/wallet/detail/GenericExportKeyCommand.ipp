namespace Xeth{


template<class Store>
GenericExportKeyCommand<Store>::GenericExportKeyCommand(const Store &store) :
    _store(store)
{}


template<class Store>
QVariant GenericExportKeyCommand<Store>::operator()(const QVariantMap &request)
{
    QString address = request["address"].toString();
    QString destination = request["path"].toString();

    if(!address.length() || !destination.length())
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(execute(address, destination));

}


template<class Store>
bool GenericExportKeyCommand<Store>::execute(const QString &address, const QString &destination)
{

    typename Store::Iterator it = _store.find(address.toStdString().c_str());

    if(it==_store.end())
    {
        return false;
    }

    const boost::filesystem::path & path = it.path();
    QString file = destination;
    file +=  QDir::separator();
    file += (const char *)path.filename().c_str();
    return QFile::copy(path.string().c_str(), file);
}


}
