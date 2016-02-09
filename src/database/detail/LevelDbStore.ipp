

namespace Xeth{

template<class Value, class Serializer>
LevelDbStore<Value, Serializer>::LevelDbStore(const char *path) :
    _db(NULL)
{
    open(path);
}

template<class Value, class Serializer>
LevelDbStore<Value, Serializer>::LevelDbStore(const std::string &path) :
    _db(NULL)
{
    open(path);
}


template<class Value, class Serializer>
LevelDbStore<Value, Serializer>::LevelDbStore() :
    _db(NULL)
{}

template<class Value, class Serializer>
void LevelDbStore<Value, Serializer>::close()
{
    if(_db)
    {
        delete _db;
    }
}

template<class Value, class Serializer>
template<class String>
void LevelDbStore<Value, Serializer>::open(const String &path)
{
    if(!openNoThrow(path))
    {
        throw std::runtime_error("failed to open DB");
    }

}

template<class Value, class Serializer>
template<class String>
bool LevelDbStore<Value, Serializer>::openNoThrow(const String &path)
{
    _path = path;

    leveldb::Options options;
    options.create_if_missing = true;

    close();

    leveldb::Status status = leveldb::DB::Open(options, path, &_db);

    return status.ok();
}



template<class Value, class Serializer>
LevelDbStore<Value, Serializer>::~LevelDbStore()
{
    close();
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::Iterator LevelDbStore<Value, Serializer>::begin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToFirst();
    return makeIterator(it);
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::Iterator LevelDbStore<Value, Serializer>::end() const
{
    return Iterator();
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::ReverseIterator LevelDbStore<Value, Serializer>::rbegin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToLast();
    return makeReverseIterator(it);
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::ReverseIterator LevelDbStore<Value, Serializer>::rend() const
{
    return ReverseIterator();
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::Iterator LevelDbStore<Value, Serializer>::find(const char *key) const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->Seek(key);
    return makeIterator(it);
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::Iterator LevelDbStore<Value, Serializer>::makeIterator(leveldb::Iterator *it) const
{
    return Iterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Value, class Serializer>
typename LevelDbStore<Value, Serializer>::ReverseIterator LevelDbStore<Value, Serializer>::makeReverseIterator(leveldb::Iterator *it) const
{
    return ReverseIterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Value, class Serializer>
Value LevelDbStore<Value, Serializer>::get(const char *key) const
{
    Value result;
    get(key, result);
    return result;
}

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::get(const char *key, Value &result) const
{
    std::string data;
    leveldb::Status status = _db->Get(leveldb::ReadOptions(), key, &data);
    if(!status.ok())
    {
        return false;
    }

    Serializer serializer;
    serializer(key, data.c_str(), result);
    return true;
}


template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::insert(const char *key, const Value &value)
{
    Serializer serializer;
    return insert(key, serializer(value).c_str());
}

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::insert(const char *key, const char *value)
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

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::move(const char *oldKey, const char *newKey)
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

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::replace(const char *key, const Value &value)
{
    Serializer serializer;
    return replace(key, serializer(value).c_str());
}

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::replace(const char *key, const char *value)
{
    leveldb::Status status = _db->Put(leveldb::WriteOptions(), key, value);
    return status.ok();
}

template<class Value, class Serializer>
bool LevelDbStore<Value, Serializer>::remove(const char *key)
{
    leveldb::Status status = _db->Delete(leveldb::WriteOptions(), key);
    return status.ok();
}



}
