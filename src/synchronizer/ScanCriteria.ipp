#include <QDebug>
#include <QThread>

namespace Xeth{

template<class Criterion, class Arg1>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1)
{
    addCriterion(minBlock, new Criterion(arg1));
}

template<class Criterion, class Arg1, class Arg2>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1, const Arg2 &arg2)
{
    addCriterion(minBlock, new Criterion(arg1, arg2));
}

template<class Criterion, class Arg1, class Arg2, class Arg3>
void ScanCriteria::addCriterion(size_t minBlock, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
   addCriterion(minBlock, new Criterion(arg1, arg2, arg3));
}

template<class BlockChain, class Progress>
size_t ScanCriteria::parse(BlockChain &blockchain, ScanResult &result, Progress &progress)
{
    emit Test();
    if(!_criteria.size())
    {
        progress.setValue(100);
        return 0;
    }

    blockchain.retrieveBlockDetails(true);
    size_t height = blockchain.getHeight();
    size_t minBlock = _criteria.begin()->first;

    if(height < minBlock)
    {
        progress.setValue(100);
        return height;
    }

    std::map<size_t, Container::iterator> mappedCriteria;

    size_t minIndex = minBlock;

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

    result.lastBlock = minIndex;


    try
    {

        for(std::map<size_t, Container::iterator>::iterator it=mappedCriteria.begin(), end=mappedCriteria.end(); it!=end; ++it)
        {

            for(; result.lastBlock <= it->first; result.lastBlock++)
            {
                Block block = blockchain.getBlock(result.lastBlock);
                processBlock(result.lastBlock, block, it->second, result);
                progress.next();
                InterruptionPoint interruption;
            }

        }
    }
    catch(const InterruptionException &)
    {}
    catch(const std::exception &e)
    {
        const char * msg = e.what();
        qDebug()<<"exception : "<<msg;
    }
    catch(...)
    {
        qDebug()<<"scan exception, interrupting";
    }

    for(Container::iterator it=_criteria.begin(), end=_criteria.end(); it!=end; ++it)
    {
        it->first = result.lastBlock;
    }

    return result.lastBlock;

}



}
