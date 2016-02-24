namespace Xeth{


template<class Key>
leveldb::Slice NumericKeySerializer<Key>::operator()(const Key &key) const
{
    return leveldb::Slice(reinterpret_cast<const char *>(&key), sizeof(key));
}


}
