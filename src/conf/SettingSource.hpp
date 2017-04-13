#pragma once

#include <QString>

namespace Xeth{



class SettingSource
{
    public:
        virtual bool has(const char *) const = 0;
        virtual QString get(const char *) const = 0;
};


}
