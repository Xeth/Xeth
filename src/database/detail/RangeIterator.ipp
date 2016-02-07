


namespace Xeth{


template<class Iterator, class Value>
RangeIterator<Iterator, Value>::RangeIterator(const Iterator &it, const Iterator &end, size_t limit) :
    Base(it),
    _end(end),
    _limit(limit),
    _offset(0)
{}


template<class Iterator, class Value>
RangeIterator<Iterator, Value>::RangeIterator() :
    Base(),
    _limit(0),
    _offset(0)
{}



template<class Iterator, class Value>
void RangeIterator<Iterator, Value>::increment()
{
    if(++_offset >= _limit)
    {
        this->base_reference() = _end;
    }
    else
    {
        ++ this->base_reference();
    }
}


}
