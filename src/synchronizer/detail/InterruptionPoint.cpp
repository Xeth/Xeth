
#include "InterruptionPoint.hpp"
#include "ScanWorker.hpp"

namespace Xeth{


InterruptionPoint::InterruptionPoint()
{
    ScanWorker * worker = dynamic_cast<ScanWorker *>(QThread::currentThread());
    if(worker)
    {
        if(worker->isInterrupted())
        {
            throw InterruptionException();
        }
    }
}


}
