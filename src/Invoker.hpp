#pragma once

#include <QVariant>

#include "Notifier.hpp"

namespace Xeth{


class NullCommandArguments
{};



class Invoker
{

    public:

        Invoker(Notifier &);

        template<class Command, class Arguments>
        QVariant invoke(Command &, const Arguments &);


    private:
        template<class Command, class Arguments>
        QVariant execute(Command &, const Arguments &);

        template<class Command>
        QVariant execute(Command &, const NullCommandArguments &);

    protected:
        Notifier &_notifier;
};



}


#include "Invoker.ipp"
