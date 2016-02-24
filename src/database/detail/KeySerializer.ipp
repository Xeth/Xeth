namespace Xeth{


template<class Key>
leveldb::Slice KeySerializer<Key>::operator()(const Key &key) const
{
    return leveldb::Slice(key);
}


}
