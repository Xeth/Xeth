namespace Xeth{


template<class Store, class ChangePasswordOperation>
GenericChangePasswordCommand<Store, ChangePasswordOperation>::GenericChangePasswordCommand(Store &store) : 
    _store(store)
{}


template<class Store, class ChangePasswordOperation>
QVariant GenericChangePasswordCommand<Store, ChangePasswordOperation>::operator()(const QVariantMap &request)
{
    if(!request.contains("address")||!request.contains("password")||!request.contains("newPassword"))
    {
        return QVariant::fromValue(false);
    }
    QString address = request["address"].toString();
    QString password = request["password"].toString();
    QString newPassword = request["newPassword"].toString();

    return QVariant::fromValue(execute(address, password, newPassword));
}


template<class Store, class ChangePasswordOperation>
bool GenericChangePasswordCommand<Store, ChangePasswordOperation>::execute(const QString &address, const QString &password, const QString &newPassword)
{
    typename Store::Iterator it = _store.find(address.toStdString().c_str());
    if(it==_store.end())
    {
        return false;
    }
    ChangePasswordOperation operation;
    try
    {
        typename Store::Data newKey = operation(*it, password, newPassword);
        return _store.replace(newKey);
    }
    catch(...)
    {}
    return false;
}



}
