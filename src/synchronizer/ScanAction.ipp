namespace Xeth{

template<class BlockChain>
void ScanAction::start(BlockChain &blockchain, ScanCriteria &criteria)
{
    _thread.reset(new boost::thread(boost::bind(&ScanAction::execute<BlockChain>, this, boost::ref(blockchain), boost::ref(criteria))));
}

template<class BlockChain>
void ScanAction::start(BlockChain &blockchain, ScanCriteria &criteria, ScanProgress &progress)
{
    _thread.reset(new boost::thread(boost::bind(&ScanAction::execute<BlockChain>, this, boost::ref(blockchain), boost::ref(criteria), boost::ref(progress))));
}


template<class BlockChain>
void ScanAction::execute(BlockChain &blockchain, ScanCriteria &criteria)
{
    _result = ScanResult();
    criteria.process(blockchain, _result);
    emit Done();
}

template<class BlockChain>
void ScanAction::execute(BlockChain &blockchain, ScanCriteria &criteria, ScanProgress &progress)
{
    _result = ScanResult();
    criteria.process(blockchain, _result, progress);
    emit Done();
}


}
