#include "AddressBookStore.hpp"

namespace Xeth{

QJsonObject AddressBookDataSerializer::operator ()(const char *key, const char *value) const
{
    QJsonObject result;
    operator()(key, value, result);
    return result;
}

bool AddressBookDataSerializer::operator ()(const char *key, const char *value, QJsonObject &result) const
{
    result.insert("alias", key);
    result.insert("address", value);
    return true;
}


std::string AddressBookDataSerializer::operator ()(const QJsonObject &object) const
{
    return object["address"].toString().toStdString();
}


AddressBookStore::AddressBookStore()
{}


AddressBookStore::AddressBookStore(const std::string &path) : Base(path)
{}


AddressBookStore::AddressBookStore(const boost::filesystem::path &path) : Base(path)
{}


bool AddressBookStore::insert(const char *alias, const char *address)
{
    QJsonObject object;
    object.insert("address", address);

    return insert(alias, object);
}

bool AddressBookStore::insert(const char *alias, const QJsonObject &object)
{
    if(Base::insert(alias, object))
    {
        emit NewItem(object);
        return true;
    }
    return false;
}



}
