
#include "ChainProgressFetcher.hpp"

namespace Xeth{


ChainProgressFetcher::ChainProgressFetcher(Ethereum::Connector::Provider &provider):
    _progress(Ethereum::Connector::BlockChain(provider))
{
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}


void ChainProgressFetcher::autoUpdate(size_t interval)
{
    _timer.start(interval);
}


void ChainProgressFetcher::update()
{
    if(_progress.update())
    {
        emit Progress(_progress.getValue());
    }

}


double ChainProgressFetcher::getValue() const
{
    return _progress.getValue();
}


void ChainProgressFetcher::stop()
{
    _timer.stop();
}


bool ChainProgressFetcher::isActive() const
{
    return _timer.isActive();
}


}
