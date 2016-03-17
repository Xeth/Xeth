namespace Xeth{


template<class Key>
leveldb::Slice KeySerializer<Key>::operator()(const Key &key) const
{
    return leveldb::Slice(key);
}

template<class Key>
std::string KeySerializer<Key>::toString(const leveldb::Slice &slice) const
{
    return slice.ToString();
}

template<class Key>
Key KeySerializer<Key>::operator()(const leveldb::Slice &slice) const
{
    return Key(slice);
}

template<class Key>
Key KeySerializer<Key>::operator()() const
{
    return Key();
}

}
