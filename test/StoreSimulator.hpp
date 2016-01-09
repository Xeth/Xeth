#pragma once

#include <vector>



template<class Value>
class StoreSimulator
{
    public:
        typedef typename std::vector<Value>::const_iterator Iterator;
        typedef typename std::vector<Value>::const_reverse_iterator ReverseIterator;
        typedef Value DataType;

    public:
        bool insert(const Value &);
        Iterator at(size_t offset) const;
        Iterator begin() const;
        Iterator end() const;
        ReverseIterator rbegin() const;
        ReverseIterator rend() const;

    private:
        std::vector<Value> _data;

};


#include "StoreSimulator.ipp"
