
#include "ChainProgressFetcher.hpp"
#include <QDebug>

namespace Xeth{


ChainProgressFetcher::ChainProgressFetcher(Ethereum::Connector::Provider &provider):
    _chain(provider),
    _progress(_chain)
{
    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}


void ChainProgressFetcher::autoUpdate(size_t interval)
{
    update();
    _timer.start(interval);
}


void ChainProgressFetcher::update()
{
    try
    {
        if(_progress.update())
        {
            emit Progress(_progress.getValue());
        }
    }
    catch(const std::exception &e)
    {
        qDebug()<<"failed to fetch progress : "<<e.what();
    }
    catch(...)
    {
        qDebug()<<"failed to fetch progress";
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
