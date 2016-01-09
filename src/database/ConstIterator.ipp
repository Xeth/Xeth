
namespace Xeth{


template<class Decoder, class Value>
ConstIterator<Decoder, Value>::ConstIterator(const boost::shared_ptr<leveldb::Iterator> &handle) :
    _handle(handle),
    _valid(handle->Valid())
{}

template<class Decoder, class Value>
ConstIterator<Decoder, Value>::ConstIterator() :
    _valid(false)
{}


template<class Decoder, class Value>
bool ConstIterator<Decoder, Value>::equal(const ConstIterator &it) const
{
    if((_valid == it._valid) && (!_valid || (_handle->key() == it._handle->key())))
    {
        return true;
    }

    return false;
}


template<class Decoder, class Value>
Value ConstIterator<Decoder, Value>::dereference() const
{
    return _decoder(_handle->key().ToString().c_str(), _handle->value().ToString().c_str());
}

template<class Decoder, class Value>
void ConstIterator<Decoder, Value>::increment()
{
    if(_valid)
    {
        _handle->Next();
        _valid = _handle->Valid();
    }
}


template<class Decoder, class Value>
void ConstIterator<Decoder, Value>::decrement()
{
    if(_valid)
    {
        _handle->Prev();
        _valid = _handle->Valid();
    }
}

}
