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

    const boost::filesystem::path & from = it.path();
    boost::filesystem::path to = boost::filesystem::absolute(destination.toStdString());
    to /= from.filename();
    to += ".backup_";
    to += boost::lexical_cast<std::string>(time(NULL));
    boost::system::error_code error;
    boost::filesystem::copy_file(from, to, boost::filesystem::copy_option::overwrite_if_exists, error);
    if(error)
    {
        return false;
    }
    return true;
}


}
