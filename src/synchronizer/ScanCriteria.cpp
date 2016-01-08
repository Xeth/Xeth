
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

size_t ScanCriteria::process(BlockChain &blockchain, QJsonArray &result, ScanProgress &progress)
{
    return process(blockchain, result, progress);
}

template<class Progress>
size_t ScanCriteria::process(BlockChain &blockchain, QJsonArray &result, Progress &progress)
{
    if(!_criteria.size())
    {
        return 0;
    }

    size_t height = blockchain.getHeight();
    size_t minBlock = _criteria.begin()->first;

    if(height < minBlock)
    {
        return height;
    }

    std::map<size_t, Container::iterator> mappedCriteria;

    size_t minIndex = minBlock;

    //3 10 10 11 12 13 14

    for(Container::iterator it=_criteria.begin(), end=_criteria.end(); it!=end; ++it)
    {
        if(minIndex < it->first)
        {
            mappedCriteria.insert(std::make_pair(minIndex, it));
            minIndex = it->first;
        }
    }

    mappedCriteria.insert(std::make_pair(height, _criteria.end()));

    progress.setRange(minBlock, height);

    size_t blockIndex = 0;
    BigInt blockReward("5000000000000000000");

    try
    {

        for(std::map<size_t, Container::iterator>::iterator it=mappedCriteria.begin(), end=mappedCriteria.end(); it!=end; ++it)
        {
            for(blockIndex = it->second->first; blockIndex < it->first; blockIndex++)
            {
                size_t prevSize = result.size();
                Block block = blockchain.getBlock(blockIndex);

                std::string miner = block.getMiner();
                std::string blockHash = block.getHash();
                time_t blockTime = block.getTimestamp();

                for(Container::iterator cIt=_criteria.begin(),cEnd=it->second; cIt!=cEnd; ++cIt)
                {
                    cIt->second->processHeader(blockIndex, blockHash, miner, blockReward, blockTime, result);
                }

                TransactionCollection transactions = block.getTransactions();

                for(TransactionCollection::Iterator tIt=transactions.begin(), tEnd=transactions.end(); tIt!=tEnd; ++tIt)
                {
                    std::string sender = tIt->getSender();
                    std::string receiver = tIt->getReceiver();
                    std::string txid = tIt->getHash();
                    BigInt amount = tIt->getAmount();
                    std::string data = tIt->getInput();

                    for(Container::iterator cIt=_criteria.begin(),cEnd=it->second; cIt!=cEnd; ++cIt)
                    {
                        cIt->second->processTransaction(txid, sender, receiver, amount, data, blockTime, result);
                    }
                }

                progress.next();
                size_t resultSize = result.size();
                if(prevSize != resultSize)
                {
                    size_t numItems = resultSize - prevSize;
                    QJsonArray::const_iterator resultEnd = result.constEnd();
                    emit Data(blockIndex, resultEnd- numItems, resultEnd);
                }

                boost::this_thread::interruption_point();
            }

        }
    }
    catch(boost::thread_interrupted &)
    {}

    for(Container::iterator it=_criteria.begin(), end=_criteria.end(); it!=end; ++it)
    {
        it->first = blockIndex;
    }

    return blockIndex;

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
