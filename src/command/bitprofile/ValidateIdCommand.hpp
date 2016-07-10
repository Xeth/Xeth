#pragma once 

#include <QString>
#include <QVariant>
#include <QRegExp>


namespace Xeth{



class ValidateIdCommand
{
    public:
        ValidateIdCommand();

        QVariant operator()(const QString &name);

    private:
        QRegExp _pattern;
};



}
