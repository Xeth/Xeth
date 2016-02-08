
namespace Xeth{


template<class BlockChain>
ChainProgress<BlockChain>::ChainProgress(const BlockChain &chain):
    _chain(chain)
{}


template<class BlockChain>
bool ChainProgress<BlockChain>::update()
{
    if(!_firstBlockTime)
    {
        typename BlockChain::Block firstBlock = _chain.getBlock(0);
        _firstBlockTime = firstBlock.getTimestamp();
    }
    size_t height = _chain.getHeight();

    typename BlockChain::Block lastBlock = _chain.getBlock(height);

    time_t now = time(NULL);
    size_t unfetchedBlocks = (now - lastBlock.getTimestamp()) / 12;

    double progress = roundf(((height * 100) / (height + unfetchedBlocks)) * 100) / 100;

    if(progress != _progress )
    {
        return true;
    }

    return false;
}


template<class BlockChain>
double ChainProgress<BlockChain>::getValue() const
{
    return _progress;
}




}
