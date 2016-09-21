#pragma once

#include <QVariant>
#include "synchronizer/Synchronizer.hpp"


namespace Xeth{


class GetScanProgressCommand
{
    public: 
        GetScanProgressCommand(Synchronizer &synchronizer);
        QVariant operator()();

    private:
        Synchronizer &_synchronizer;
};


}
