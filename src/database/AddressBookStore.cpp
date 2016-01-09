#include "AddressBookStore.hpp"

namespace Xeth{

QJsonObject AddressBookDataDecoder::operator ()(const char *key, const char *value) const
{
    QJsonObject result;
    operator()(key, value, result);
    return result;
}

bool AddressBookDataDecoder::operator ()(const char *key, const char *value, QJsonObject &result) const
{
    result.insert("alias", key);
    result.insert("address", value);
    return true;
}


std::string AddressBookDataDecoder::operator ()(const QJsonObject &object) const
{
    return object["address"].toString().toStdString();
}



AddressBookStore::AddressBookStore()
{}

AddressBookStore::AddressBookStore(const std::string &path) : Base(path)
{}

bool AddressBookStore::insert(const char *alias, const char *address)
{
    QJsonObject object;
    object.insert("address", address);

    return Base::insert(alias, address);
}



}
