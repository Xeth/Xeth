#include "ChainProgress.hpp"


namespace Xeth{


ChainProgress::ChainProgress(Ethereum::Connector::Provider &provider):
    _chain(provider)
{
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void ChainProgress::autoUpdate(size_t interval)
{
    _timer.start(interval);
}

void ChainProgress::update()
{
    if(!_firstBlockTime)
    {
        Ethereum::Connector::Block firstBlock = _chain.getBlock(0);
        _firstBlockTime = firstBlock.getTimestamp();
    }
    size_t height = _chain.getHeight();

    Ethereum::Connector::Block lastBlock = _chain.getBlock(height);

    time_t now = time(NULL);
    size_t unfetchedBlocks = (now - lastBlock.getTimestamp()) / 12;

    double progress = roundf(((height * 100) / (height + unfetchedBlocks)) * 100) / 100;

    if(progress != _progress )
    {
        _progress = progress;
        emit Progress(progress);
    }

}

double ChainProgress::getValue() const
{
    return _progress;
}


void ChainProgress::stop()
{
    _timer.stop();
}

bool ChainProgress::isActive() const
{
    return _timer.isActive();
}

}
