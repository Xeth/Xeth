

namespace Xeth{

template<class Store>
DataRange<Store>::DataRange(Store &store) :
    _store(store),
    _limit(0),
    _offset(0)
{}

template<class Store>
void DataRange<Store>::setLimit(size_t limit)
{
    _limit = limit;
}

template<class Store>
void DataRange<Store>::setOffset(size_t offset)
{
    _offset = offset;
}


template<class Store>
typename DataRange<Store>::Iterator DataRange<Store>::begin() const
{
    return Iterator(_store.at(_offset), _store.end(), _limit);
}

template<class Store>
typename DataRange<Store>::Iterator DataRange<Store>::end() const
{
    return Iterator(_store.end(), _store.end(), 0);
}


template<class Store>
typename DataRange<Store>::ReverseIterator DataRange<Store>::rbegin() const
{
    return ReverseIterator(typename Store::ReverseIterator(_store.at(_offset, true)), _store.rend(), _limit);
}

template<class Store>
typename DataRange<Store>::ReverseIterator DataRange<Store>::rend() const
{
    return ReverseIterator(_store.rend(), _store.rend(), 0);
}


}
