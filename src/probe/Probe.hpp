#pragma once

#include <QObject>
#include "conf/Settings.hpp"


namespace Xeth{



class Probe : public QObject
{
    Q_OBJECT
    public:

        virtual bool operator()(const Settings &) const = 0;
        virtual ~Probe();

    signals:
        void Warning(const QString &) const;
        void Error(const QString &) const;
};


}
