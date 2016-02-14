#pragma once 

#include <QObject>

#include "synchronizer/Synchronizer.hpp"
#include "Notifier.hpp"


namespace Xeth{


class ProgressFacade : public QObject
{
    Q_OBJECT
    public:
        ProgressFacade(Synchronizer &, Notifier &);

        QVariant getScanProgress() const;
        QVariant getSyncProgress() const;


    private:
        Synchronizer &_synchronizer;
};


}
