

namespace Xeth{

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::LevelDbStore(const char *path) :
    _db(NULL)
{
    open(path);
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::LevelDbStore(const std::string &path) :
    _db(NULL)
{
    open(path);
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::LevelDbStore(const boost::filesystem::path &path) :
    _db(NULL)
{
    open(path.string());
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::LevelDbStore() :
    _db(NULL)
{}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
void LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::close()
{
    if(_db)
    {
        delete _db;
    }
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
template<class String>
void LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::open(const String &path)
{
    if(!openNoThrow(path))
    {
        throw std::runtime_error("failed to open DB");
    }

}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
template<class String>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::openNoThrow(const String &path)
{
    _path = path;

    leveldb::Options options = makeOptions(_comparator);
    options.create_if_missing = true;

    close();

    leveldb::Status status = leveldb::DB::Open(options, path, &_db);

    return status.ok();
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
void LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::open(const boost::filesystem::path &path)
{
    open(path.string());
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::openNoThrow(const boost::filesystem::path &path)
{
    return openNoThrow(path.string());
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::~LevelDbStore()
{
    close();
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::Iterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::begin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToFirst();
    return makeIterator(it);
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::Iterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::end() const
{
    return Iterator();
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::ReverseIterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::rbegin() const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->SeekToLast();
    return makeReverseIterator(it);
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::ReverseIterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::rend() const
{
    return ReverseIterator();
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::Iterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::find(const Key &key) const
{
    leveldb::Iterator *it = _db->NewIterator(leveldb::ReadOptions());
    it->Seek(makeKey(key));
    return makeIterator(it);
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::Iterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeIterator(leveldb::Iterator *it) const
{
    return Iterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
typename LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::ReverseIterator 
LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeReverseIterator(leveldb::Iterator *it) const
{
    return ReverseIterator(boost::shared_ptr<leveldb::Iterator>(it));
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
Value LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::get(const Key &key) const
{
    Value result = Value();
    get(key, result);
    return result;
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::get(const Key &key, Value &result) const
{
    std::string data;

    leveldb::Status status = _db->Get(leveldb::ReadOptions(), makeKey(key), &data);
    if(!status.ok())
    {
        return false;
    }

    ValueSerializer serializer;
    serializer(key, data.c_str(), result);
    return true;
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::insert(const Key &key, const Value &value)
{
    return insert(makeKey(key), makeValue(value).c_str());
}



template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::move(const Key &oldKey, const Key &newKey)
{
    return move(makeKey(oldKey), makeKey(newKey));
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::replace(const Key &key, const Value &value)
{
    return replace(makeKey(key), makeValue(value).c_str());
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::remove(const Key &key)
{
    return remove(makeKey(key));
}


////


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::replace(const leveldb::Slice &key, const leveldb::Slice &value)
{
    leveldb::Status status = _db->Put(leveldb::WriteOptions(), key, value);
    return status.ok();
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::remove(const leveldb::Slice &key)
{
    leveldb::Status status = _db->Delete(leveldb::WriteOptions(), key);
    return status.ok();
}

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::move(const leveldb::Slice &oldKey, const leveldb::Slice &newKey)
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

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
bool LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::insert(const leveldb::Slice &key, const leveldb::Slice &value)
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

template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
template<class Comparator>
leveldb::Options LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeOptions(const Comparator &comparator)
{
    leveldb::Options options;
    options.comparator = &comparator;
    return options;
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
leveldb::Options LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeOptions(const DefaultKeyComparator &comparator)
{
    return leveldb::Options();
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
std::string LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeValue(const Value &value) const
{
    ValueSerializer serializer;
    return serializer(value);
}


template<class Value, class ValueSerializer, class Key, class KeySerializer, class KeyComparator>
leveldb::Slice LevelDbStore<Value, ValueSerializer, Key, KeySerializer, KeyComparator>::makeKey(const Key &key) const
{
    KeySerializer serializer;
    return serializer(key);
}




}
