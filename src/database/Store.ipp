

namespace Xeth{

template<class Decoder, class Value>
Store<Decoder, Value>::Store(const char *path) :
    _db(NULL)
{
    open(path);
}

template<class Decoder, class Value>
Store<Decoder, Value>::Store(const std::string &path) :
    _db(NULL)
{
    open(path);
}


template<class Decoder, class Value>
Store<Decoder, Value>::Store() :
    _db(NULL)
{}

template<class Decoder, class Value>
void Store<Decoder, Value>::close()
{
    if(_db)
    {
        delete _db;
    }
}

template<class Decoder, class Value>
template<class String>
void Store<Decoder, Value>::open(const String &path)
{
    if(!openNoThrow(path))
    {
        throw std::runtime_error("failed to open DB");
    }

}

template<class Decoder, class Value>
template<class String>
bool Store<Decoder, Value>::openNoThrow(const String &path)
{
    _path = path;

    leveldb::Options options;
    options.create_if_missing = true;

    close();

    leveldb::Status status = leveldb::DB::Open(options, path, &_db);

    return status.ok();
}



template<class Decoder, class Value>
Store<Decoder, Value>::~Store()
{
    close();
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::Iterator Store<Decoder, Value>::begin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToFirst();
    return makeIterator(it);
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::Iterator Store<Decoder, Value>::end() const
{
    return Iterator(false);
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::ReverseIterator Store<Decoder, Value>::rbegin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToLast();
    return makeReverseIterator(it);
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::ReverseIterator Store<Decoder, Value>::rend() const
{
    return ReverseIterator(false);
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::Iterator Store<Decoder, Value>::find(const char *key) const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->Seek(key);
    return makeIterator(it);
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::Iterator Store<Decoder, Value>::makeIterator(leveldb::Iterator *it) const
{
    return Iterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Decoder, class Value>
typename Store<Decoder, Value>::ReverseIterator Store<Decoder, Value>::makeReverseIterator(leveldb::Iterator *it) const
{
    return ReverseIterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Decoder, class Value>
Value Store<Decoder, Value>::get(const char *key) const
{
    Value result;
    get(key, result);
    return result;
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::get(const char *key, Value &result) const
{
    std::string data;
    leveldb::Status status = _db->Get(leveldb::ReadOptions(), key, &data);
    if(!status.ok())
    {
        return false;
    }

    Decoder decoder;
    decoder(key, data.c_str(), result);
    return true;
}


template<class Decoder, class Value>
bool Store<Decoder, Value>::insert(const char *key, const Value &value)
{
    Decoder decoder;
    return insert(key, decoder(value).c_str());
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::insert(const char *key, const char *value)
{
    std::string oldValue;
    leveldb::Status status = _db->Get(leveldb::ReadOptions(), key, &oldValue);
    if(status.ok())
    {
        return false;
    }

    status = _db->Put(leveldb::WriteOptions(), key, value);
    return status.ok();
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::move(const char *oldKey, const char *newKey)
{
    std::string data;
    leveldb::Status status = _db->Get(leveldb::ReadOptions(), oldKey, &data);
    if(!status.ok())
    {
        return false;
    }

    status = _db->Put(leveldb::WriteOptions(), newKey, data);
    if(!status.ok())
    {
        return false;
    }

    status = _db->Delete(leveldb::WriteOptions(), oldKey);

    return status.ok();
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::replace(const char *key, const Value &value)
{
    Decoder decoder;
    return replace(key, decoder(value).c_str());
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::replace(const char *key, const char *value)
{
    leveldb::Status status = _db->Put(leveldb::WriteOptions(), key, value);
    return status.ok();
}

template<class Decoder, class Value>
bool Store<Decoder, Value>::remove(const char *key)
{
    leveldb::Status status = _db->Delete(leveldb::WriteOptions(), key);
    return status.ok();
}



}
