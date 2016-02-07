

namespace Xeth{

template<class Decoder, class Value>
LevelDbReverseIterator<Decoder, Value>::LevelDbReverseIterator(const LevelDbIterator<Decoder, Value> &it) :
    Base(it)
{}

template<class Decoder, class Value>
LevelDbReverseIterator<Decoder, Value>::LevelDbReverseIterator(const boost::shared_ptr<leveldb::Iterator> &it) :
    Base(it)
{}

template<class Decoder, class Value>
LevelDbReverseIterator<Decoder, Value>::LevelDbReverseIterator() :
    Base()
{}

template<class Decoder, class Value>
void LevelDbReverseIterator<Decoder, Value>::increment()
{
    -- this->base_reference();
}

template<class Decoder, class Value>
void LevelDbReverseIterator<Decoder, Value>::decrement()
{
    ++ this->base_reference();
}

}
