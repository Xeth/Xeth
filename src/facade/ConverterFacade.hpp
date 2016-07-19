#pragma once

#include <QVariant>
#include <QVariantMap>

#include "command/Invoker.hpp"
#include "command/converter/FromSzaboCommand.hpp"
#include "command/converter/ToSzaboCommand.hpp"
#include "command/converter/FromFinneyCommand.hpp"
#include "command/converter/ToFinneyCommand.hpp"
#include "command/converter/FromWeiCommand.hpp"
#include "command/converter/ToWeiCommand.hpp"

#include "Notifier.hpp"


namespace Xeth{


class ConverterFacade : public QObject
{
    Q_OBJECT

    public:

        ConverterFacade(Invoker<Notifier> &invoker);

        Q_INVOKABLE QVariant fromFinney(const QVariant &);
        Q_INVOKABLE QVariant toFinney(const QVariant &);
        Q_INVOKABLE QVariant fromSzabo(const QVariant &);
        Q_INVOKABLE QVariant toSzabo(const QVariant &);
        Q_INVOKABLE QVariant fromWei(const QVariant &);
        Q_INVOKABLE QVariant toWei(const QVariant &);


    private:
        Invoker<Notifier> &_invoker;
};


}
