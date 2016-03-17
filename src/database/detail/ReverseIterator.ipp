

namespace Xeth{

template<class Iterator>
ReverseIterator<Iterator>::ReverseIterator(const Iterator &it) :
    Base(it)
{}


template<class Iterator>
ReverseIterator<Iterator>::ReverseIterator() :
    Base()
{}

template<class Iterator>
void ReverseIterator<Iterator>::increment()
{
    -- this->base_reference();
}

template<class Iterator>
void ReverseIterator<Iterator>::decrement()
{
    ++ this->base_reference();
}

}
