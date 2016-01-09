

namespace Xeth{

template<class Store>
StoreRange<Store>::StoreRange(Store &store) :
    _store(store),
    _limit(0),
    _offset(0)
{}

template<class Store>
void StoreRange<Store>::setLimit(size_t limit)
{
    _limit = limit;
}

template<class Store>
void StoreRange<Store>::setOffset(size_t offset)
{
    _offset = offset;
}


template<class Store>
typename StoreRange<Store>::Iterator StoreRange<Store>::begin() const
{
    return Iterator(_store.at(_offset), _limit);
}

template<class Store>
typename StoreRange<Store>::Iterator StoreRange<Store>::end() const
{
    return Iterator();
}


}
