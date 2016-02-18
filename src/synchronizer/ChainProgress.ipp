
namespace Xeth{


template<class BlockChain>
ChainProgress<BlockChain>::ChainProgress(BlockChain &chain):
    _chain(chain),
    _progress(0)
{}


template<class BlockChain>
bool ChainProgress<BlockChain>::update()
{
    double progress;
    size_t height = _chain.getHeight();

    if(!height)
    {
        progress = 0;
    }
    else
    {
        typename BlockChain::Block lastBlock = _chain.getBlock(height);
        time_t now = time(NULL);
        size_t unfetchedBlocks = (now - lastBlock.getTimestamp()) / 12;

        progress = (double)(height * 100) / (double)(height + unfetchedBlocks);
        if(progress > 100)
        {
            progress = 100;
        }
    }
    if(progress != _progress )
    {
        _progress = progress;
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
