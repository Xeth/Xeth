#pragma once

#include <QVariant>
#include "synchronizer/Synchronizer.hpp"


namespace Xeth{


class GetSyncProgressCommand
{
    public: 
        GetSyncProgressCommand(Synchronizer &synchronizer);
        QVariant operator()();

    private:
        Synchronizer &_synchronizer;
};


}
