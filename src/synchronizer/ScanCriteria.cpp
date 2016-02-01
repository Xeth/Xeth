
#include "ScanCriteria.hpp"

namespace Xeth{

ScanCriteria::ScanCriteria() : QObject()
{}

ScanCriteria::ScanCriteria(const ScanCriteria &) : QObject()
{}

ScanCriteria::~ScanCriteria()
{
    clear();
}

void ScanCriteria::clear()
{
    for(Container::iterator it=_criteria.begin(), end=_criteria.end(); it!=end; ++it)
    {
        delete it->second;
    }
    _criteria.clear();
}

ScanCriteria::Iterator ScanCriteria::begin() const
{
    return Iterator(_criteria.begin());
}

ScanCriteria::Iterator ScanCriteria::end() const
{
    return Iterator(_criteria.end());
}


void ScanCriteria::addCriterion(size_t minBlock, ScanCriterion *criterion)
{

    Container::iterator it = std::lower_bound(_criteria.begin(), _criteria.end(), minBlock, CriterionCompare());
    if(it==_criteria.end())
    {
        _criteria.push_front(std::make_pair(minBlock, criterion));
    }
    else
    {
        _criteria.insert(it, std::make_pair(minBlock, criterion));
    }
}


size_t ScanCriteria::process(BlockChain &blockchain, QJsonArray &result)
{
    DummyScanProgress progress;
    return process(blockchain, result, progress);
}



bool ScanCriteria::CriterionCompare::operator ()(const std::pair<size_t, ScanCriterion *> &criterion, size_t minBlock)
{
    return minBlock < criterion.first;
}


ScanCriteria::Iterator::Iterator() : iterator_adaptor_() {}

ScanCriteria::Iterator::Iterator(const iterator_adaptor_::base_type & p) :
    iterator_adaptor_(p) {}

const ScanCriterion & ScanCriteria::Iterator::dereference() const
{
    return *this->base()->second;
}




}
