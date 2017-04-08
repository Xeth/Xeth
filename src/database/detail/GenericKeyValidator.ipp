#include <QDebug>
namespace Xeth{


template<class Key, class Unlocker>
bool GenericKeyValidator<Key, Unlocker>::operator()(Key &key, const std::string &password) const
{
    Unlocker unlocker;
    try
    {
        unlocker(key, password);
        return true;
    }
    catch(...)
    {}
    qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~ got unlock exception";
    return false;
}


template<class Key, class Unlocker>
bool GenericKeyValidator<Key, Unlocker>::operator()(Key &key, const QString &password) const
{
    return operator()(key, password.toStdString());
}


template<class Key, class Unlocker>
bool GenericKeyValidator<Key, Unlocker>::operator()(Key &key, const char *password) const
{
    return operator()(key, std::string(password));
}



}
