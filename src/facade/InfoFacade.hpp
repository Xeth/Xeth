#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "../version.hpp"


namespace Xeth{


class InfoFacade : public QObject
{
    Q_OBJECT

    public:
        Q_INVOKABLE QString getVersion() const;

};


}
