#include "TransactionStore.hpp"


namespace Xeth{


QJsonObject TransactionDataDecoder::operator()(const char *key, const char *value) const
{
    QJsonObject result;
    operator()(key, value, result);
    return result;
}

bool TransactionDataDecoder::operator()(const char *key, const char *value, QJsonObject &result) const
{
    QJsonDocument document = QJsonDocument::fromJson(value);
    result = document.object();
    result.insert("index", boost::lexical_cast<int>(key));
    return true;
}

std::string TransactionDataDecoder::operator ()(const QJsonObject &object) const
{
    QJsonDocument document(object);
    return document.toJson().toStdString();
}



std::string TransactionIndexDecoder::operator ()(const char *, const char *value) const
{
    return value;
}

bool TransactionIndexDecoder::operator()(const char *, const char *value, std::string &result) const
{
    result = value;
    return true;
}

std::string TransactionIndexDecoder::operator ()(const std::string &index) const
{
    return index;
}

TransactionStore::TransactionStore()
{}

TransactionStore::TransactionStore(const std::string &path )
{
    open(path);
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
        QJsonObject lastTransaction = *it;
        _lastIndex = boost::lexical_cast<int>(lastTransaction["index"].toString().toStdString());
    }
    else
    {
        _lastIndex = -1;
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





QJsonObject TransactionStore::get(const char *hash) const
{
    std::string index = _indexStore.get(hash);
    if(!index.length())
    {
        return QJsonObject();
    }

    return _dataStore.get(index.c_str());
}

TransactionStore::Iterator TransactionStore::begin() const
{
    return _dataStore.begin();
}

TransactionStore::Iterator TransactionStore::end() const
{
    return _dataStore.end();
}

TransactionStore::Iterator TransactionStore::at(int index) const
{
    return _dataStore.find(boost::lexical_cast<std::string>(index).c_str());
}

TransactionStore::ReverseIterator TransactionStore::rbegin() const
{
    return _dataStore.rbegin();
}

TransactionStore::ReverseIterator TransactionStore::rend() const
{
    return _dataStore.rend();
}

bool TransactionStore::insert(const QJsonObject &obj)
{
    std::string index = getNextIndex();

    if(!_indexStore.replace(obj["hash"].toString().toStdString().c_str(), index))
    {
        return false;
    }

    return _dataStore.replace(index.c_str(), obj);
}

std::string TransactionStore::getNextIndex()
{
    return boost::lexical_cast<std::string>(++_lastIndex);
}


}
