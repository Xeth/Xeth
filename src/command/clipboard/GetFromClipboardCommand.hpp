#pragma once 

#include <QVariant>
#include <QClipboard>
#include <QApplication>


namespace Xeth{


class GetFromClipboardCommand
{
    public:
        QVariant operator()();
};


}
