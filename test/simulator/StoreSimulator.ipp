

template<class Value>
bool StoreSimulator<Value>::insert(const Value &value)
{
    _data.push_back(value);
    return true;
}


template<class Value>
typename StoreSimulator<Value>::Iterator StoreSimulator<Value>::begin() const
{
    return _data.begin();
}


template<class Value>
typename StoreSimulator<Value>::Iterator StoreSimulator<Value>::end() const
{
    return _data.end();
}


template<class Value>
typename StoreSimulator<Value>::Iterator StoreSimulator<Value>::at(size_t offset) const
{
    if(offset > _data.size())
    {
        return _data.end();
    }

    Iterator it = _data.begin();
    it += offset;

    return it;
}


template<class Value>
typename StoreSimulator<Value>::ReverseIterator StoreSimulator<Value>::rbegin() const
{
    return _data.rbegin();
}


template<class Value>
typename StoreSimulator<Value>::ReverseIterator StoreSimulator<Value>::rend() const
{
    return _data.rend();
}
