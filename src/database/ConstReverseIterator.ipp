

namespace Xeth{

template<class Decoder, class Value>
ConstReverseIterator<Decoder, Value>::ConstReverseIterator(const ConstIterator<Decoder, Value> &it) :
    Base(it)
{}

template<class Decoder, class Value>
ConstReverseIterator<Decoder, Value>::ConstReverseIterator(const boost::shared_ptr<leveldb::Iterator> &it) :
    Base(it)
{}

template<class Decoder, class Value>
ConstReverseIterator<Decoder, Value>::ConstReverseIterator(bool valid) :
    Base(valid)
{}

template<class Decoder, class Value>
void ConstReverseIterator<Decoder, Value>::increment()
{
    -- this->base_reference();
}

template<class Decoder, class Value>
void ConstReverseIterator<Decoder, Value>::decrement()
{
    ++ this->base_reference();
}

}
