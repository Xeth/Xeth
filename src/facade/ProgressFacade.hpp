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

        Q_INVOKABLE QVariant getScan() const;
        Q_INVOKABLE QVariant getSync() const;


    private:
        Synchronizer &_synchronizer;
};


}
