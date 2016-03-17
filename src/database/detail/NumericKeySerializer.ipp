namespace Xeth{


template<class Key>
leveldb::Slice NumericKeySerializer<Key>::operator()(const Key &key) const
{
    return leveldb::Slice(reinterpret_cast<const char *>(&key), sizeof(key));
}

template<class Key>
std::string NumericKeySerializer<Key>::toString(const leveldb::Slice &slice) const
{
    return boost::lexical_cast<std::string>(*reinterpret_cast<const Key *>(slice.data()));
}


}
