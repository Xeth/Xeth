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



//TransactionStore::TransactionStore(const char *chroot)
//{
//    std::string path = chroot;
//    path+="transactions";
//    leveldb::Options options;
//    options.create_if_missing = true;
//    leveldb::Status status = leveldb::DB::Open(options, path.c_str(), &_txDb);
//    if(!status.ok())
//    {
//        throw std::runtime_error("failed to open Transaction DB");
//    }

//    path+="_index";
//    status = leveldb::DB::Open(options, path.c_str(), &_txIndex);
//    if(!status.ok())
//    {
//        throw std::runtime_error("failed to open Transaction Index DB");
//    }

//    leveldb::Iterator* it = _txDb->NewIterator(leveldb::ReadOptions());
//    if(it->Valid())
//    {
//        it->SeekToLast();
//        _lastIndex = boost::lexical_cast<uint64_t>(it->key().data());
//    }
//    else
//    {
//        _lastIndex = 0;
//    }

//}

//TransactionStore::~TransactionStore()
//{
//    delete _txDb;
//    delete _txIndex;
//}

//std::string TransactionStore::getNextIndex()
//{
//    _lastIndex++;
//    return boost::lexical_cast<std::string>(_lastIndex);

//}



//bool TransactionStore::add(const TransactionCategory &category, const char *hash, const char *src, const char *dest, const BigInt &amount, time_t time)
//{
//    QJsonObject json;
//    json["hash"] = hash;
//    json["category"] = category.toString();
//    json["from"] = src;
//    json["to"] = dest;
//    json["amount"] = amount.str().c_str();
//    json["time"] = (int)time;

//    std::string index = getNextIndex();
//    QJsonDocument document(json);
//    leveldb::Status status = _txDb->Put(leveldb::WriteOptions(), index, document.rawData(NULL));
//    if(!status.ok())
//    {
//        return false;
//    }


//    status = _txIndex->Put(leveldb::WriteOptions(), hash, index);
//    return status.ok();
//}

//bool TransactionStore::add(QVariantList::const_iterator begin, QVariantList::const_iterator end)
//{
//    leveldb::WriteBatch transactionBatch;
//    leveldb::WriteBatch indexBatch;
//    for(QVariantList::const_iterator it = begin; it != end; ++it)
//    {
//        std::string index = getNextIndex();
//        QJsonDocument document = QJsonDocument::fromVariant(*it);
//        transactionBatch.Put(index, document.rawData(NULL));

//        const QVariantMap &map = *reinterpret_cast<const QVariantMap *>(it->constData());
//        const QString *hash = reinterpret_cast<const QString *>(map["hash"].constData());
//        indexBatch.Put((const char *)hash->constData(), index);
//    }

//    leveldb::Status status = _txDb->Write(leveldb::WriteOptions(), &transactionBatch);

//    if(!status.ok())
//    {
//        return false;
//    }

//    status = _txIndex->Write(leveldb::WriteOptions(), &indexBatch);

//    return status.ok();
//}

//QVariant TransactionStore::getByHash(const char *hash)
//{
//    std::string index, value;
//    leveldb::Status status = _txIndex->Get(leveldb::ReadOptions(), hash, &index);
//    if(!status.ok())
//    {
//        return QVariant::fromValue(false);
//    }
//    status = _txDb->Get(leveldb::ReadOptions(), index, &value);
//    if(!status.ok())
//    {
//        return QVariant::fromValue(false);
//    }
//    QJsonDocument document = QJsonDocument::fromRawData(value.c_str(), value.size());
//    return document.toVariant();
//}


//QVariant TransactionStore::listByTime(size_t limit, size_t offset)
//{
//    leveldb::Iterator* it = _txDb->NewIterator(leveldb::ReadOptions());
//    if(offset)
//    {
//        if(offset < _lastIndex)
//        {
//            it->Seek(boost::lexical_cast<std::string>(_lastIndex-offset));
//        }
//        else
//        {
//            it->SeekToFirst();
//        }
//    }
//    else
//    {
//        it->SeekToLast();
//    }

//    QVariantList list;

//    for(;it->Valid()&&(limit>0); it->Prev(), --limit)
//    {

//        leveldb::Slice value = it->value();
//        QJsonDocument document = QJsonDocument::fromRawData(value.data(), value.size());
//        list.push_back(document.toVariant());
//    }
//    return QVariant::fromValue(list);
//}


}
