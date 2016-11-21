#pragma once

#include <QString>
#include <QCoreApplication>

namespace Xeth{


class ApplicationPath
{
    public:
        static QString EthereumData();
        static QString XethData();
        static QString Vendors();
        static QString LocalVendors();
        static QString Keys();
        static QString TestnetKeys();
        static QString StealthKeys();
        static QString TestnetStealthKeys();
};


}
