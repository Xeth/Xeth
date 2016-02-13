#pragma once

#include <QVariant>
#include <QVariantMap>

#include "Invoker.hpp"

#include "command/converter/FromSzaboCommand.hpp"
#include "command/converter/ToSzaboCommand.hpp"
#include "command/converter/FromFinneyCommand.hpp"
#include "command/converter/ToFinneyCommand.hpp"
#include "command/converter/FromWeiCommand.hpp"
#include "command/converter/ToWeiCommand.hpp"


namespace Xeth{


class ConverterFacade : public QObject
{
    Q_OBJECT

    public:

        QVariant fromFinney(const QVariant &);
        QVariant toFinney(const QVariant &);
        QVariant fromSzabo(const QVariant &);
        QVariant toSzabo(const QVariant &);
        QVariant fromWei(const QVariant &);
        QVariant toWei(const QVariant &);


    private:
        Invoker _invoker;
};


}
