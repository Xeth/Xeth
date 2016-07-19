#pragma once

#include <QVariant>
#include <QFutureSynchronizer>
#include <QtConcurrent>

#include "Future.hpp"

namespace Xeth{


class NullCommandArguments
{};


template<class Notifier>
class Invoker
{

    public:

        Invoker(Notifier &);
        ~Invoker();

        template<class Command, class Arguments>
        QVariant invoke(Command &, const Arguments &);

        template<class Command>
        QVariant invoke(Command &);

        template<class Command>
        Future * invokeAsync(Command &);

        template<class Command, class Arguments>
        Future * invokeAsync(Command &, const Arguments &, bool synchronize = false);

        void waitToComplete();

    private:
        Invoker(const Invoker &);

        template<class Command, class Arguments>
        QVariant execute(Command &, const Arguments &);

        template<class Command>
        QVariant execute(Command &, const NullCommandArguments &);

    protected:
        Notifier &_notifier;
        QFutureSynchronizer<QVariant> _futures;
};



}


#include "Invoker.ipp"
