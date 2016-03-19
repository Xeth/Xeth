#include "TransactionStore.hpp"

namespace Xeth{


QJsonObject TransactionDataSerializer::operator()(const char *key, const char *value) const
{
    QJsonObject result;
    operator()(key, value, result);
    return result;
}

bool TransactionDataSerializer::operator()(int key, const char *value, QJsonObject &result) const
{
    DataSerializer<QJsonObject>::operator()(NULL, value, result);
    result.insert("index", key);
    return true;
}


TransactionStore::TransactionStore()
{}


TransactionStore::TransactionStore(const std::string &path )
{
    open(path);
}


TransactionStore::TransactionStore(const boost::filesystem::path &path)
{
    open(path.string());
}


bool TransactionStore::openNoThrow(const std::string &path)
{
    if(!_dataStore.openNoThrow(path) || !_indexStore.openNoThrow(path+".index"))
    {
        return false;
    }


    ReverseIterator it = _dataStore.rbegin();
    if(it != _dataStore.rend())
    {
        _lastIndex = it.base().key();
    }
    else
    {
        _lastIndex = 0;
    }

    return true;
}


void TransactionStore::open(const std::string &path)
{
    if(!openNoThrow(path))
    {
        std::stringstream stream;
        stream<<"failed to open transactions DB : "<<path;
        throw std::runtime_error(stream.str());
    }
}


bool TransactionStore::openNoThrow(const boost::filesystem::path &path)
{
    return openNoThrow(path.string());
}


void TransactionStore::open(const boost::filesystem::path &path)
{
    return open(path.string());
}


TransactionStore::Iterator TransactionStore::begin() const
{
    return _dataStore.begin();
}


TransactionStore::Iterator TransactionStore::end() const
{
    return _dataStore.end();
}


size_t TransactionStore::size() const
{
    return _lastIndex;
}

TransactionStore::Iterator TransactionStore::at(int index) const
{
    return _dataStore.find(index + 1);
}


TransactionStore::ReverseIterator TransactionStore::rbegin() const
{
    return _dataStore.rbegin();
}


TransactionStore::ReverseIterator TransactionStore::rend() const
{
    return _dataStore.rend();
}


bool TransactionStore::insert
(
    const TransactionCategory &category,
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const BigInt &amount,
    time_t timestamp
)
{
    QJsonObject obj;
    obj.insert("category", category.toString());
    obj.insert("hash", hash.c_str());
    if(from.size())
    {
        obj.insert("from",  from.c_str());
    }
    obj.insert("to", to.c_str());
    obj.insert("amount", boost::lexical_cast<std::string>(amount).c_str());
    obj.insert("timestamp", (int)timestamp);
    return insert(makeID(category, hash), obj);
}

bool TransactionStore::insert
(
    const TransactionCategory &category,
    const std::string &hash,
    const std::string &from,
    const std::string &to,
    const Ethereum::Stealth::Address &stealth,
    const BigInt &amount,
    time_t timestamp
)
{
    QJsonObject obj;
    obj.insert("category", category.toString());
    obj.insert("hash", hash.c_str());
    if(from.size())
    {
        obj.insert("from",  from.c_str());
    }
    obj.insert("to", to.c_str());
    obj.insert("amount", boost::lexical_cast<std::string>(amount).c_str());
    obj.insert("timestamp", (int)timestamp);
    obj.insert("stealth", stealth.toString().c_str());
    return insert(makeID(category, hash), obj);
}

bool TransactionStore::insert(const QJsonObject &obj)
{
    return insert(makeID(obj), obj);
}

bool TransactionStore::insert(const std::string &id, const QJsonObject &obj)
{
    int index = _indexStore.get(id.c_str());
    if(!index)
    {
        index = getNextIndex();

        if(!_indexStore.insert(id.c_str(), index))
        {
            return false;
        }

        if(!_dataStore.insert(index, obj))
        {
            return false;
        }
    }
    else
    {
        if(!_dataStore.insert(index, obj))
        {
            return false;
        }
    }
    emit NewItem(obj);
    return true;
}

std::string TransactionStore::makeID(const TransactionCategory &category, const std::string &hash)
{
    return hash + category.toString();
}


std::string TransactionStore::makeID(const QJsonObject &obj)
{
    return obj["hash"].toString().toStdString()+obj["category"].toString().toStdString();
}

int TransactionStore::getNextIndex()
{
    return ++_lastIndex;
}


}
