#pragma once


#include <QVariant>
#include "../../version.hpp"


namespace Xeth{


class GetVersionCommand
{
    public:
        QString operator()();
};


}
