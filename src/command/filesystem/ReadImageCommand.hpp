#pragma once


#include <QVariant>
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QBuffer>


namespace Xeth{


class ReadImageCommand
{
    public:
        QVariant operator()(const QString &);
};


}
