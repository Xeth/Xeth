
namespace Xeth{


template<class DataDecoder, class Value, class KeyDecoder, class Key>
LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::LevelDbIterator(const boost::shared_ptr<leveldb::Iterator> &handle) :
    _handle(handle),
    _valid(handle->Valid())
{}

template<class DataDecoder, class Value, class KeyDecoder, class Key>
LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::LevelDbIterator() :
    _valid(false)
{}


template<class DataDecoder, class Value, class KeyDecoder, class Key>
Key LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::key() const
{
    return _valid ? _keyDecoder(_handle->key()) : _keyDecoder();
}


template<class DataDecoder, class Value, class KeyDecoder, class Key>
std::string LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::keyString() const
{
    return _valid ? _keyDecoder.toString(_handle->key()) : "";
}


template<class DataDecoder, class Value, class KeyDecoder, class Key>
bool LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::equal(const LevelDbIterator &it) const
{
    if((_valid == it._valid) && (!_valid || (_handle->key() == it._handle->key())))
    {
        return true;
    }

    return false;
}


template<class DataDecoder, class Value, class KeyDecoder, class Key>
Value LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::dereference() const
{
    return _dataDecoder(_handle->key().ToString().c_str(), _handle->value().ToString().c_str());
}

template<class DataDecoder, class Value, class KeyDecoder, class Key>
void LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::increment()
{
    if(_valid)
    {
        _handle->Next();
        _valid = _handle->Valid();
    }
}


template<class DataDecoder, class Value, class KeyDecoder, class Key>
void LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>::decrement()
{
    if(_valid)
    {
        _handle->Prev();
        _valid = _handle->Valid();
    }
}

}
