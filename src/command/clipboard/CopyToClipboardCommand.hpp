#pragma once 

#include <QVariant>
#include <QVariantMap>
#include <QString>
#include <QClipboard>
#include <QApplication>


namespace Xeth{


class CopyToClipboardCommand
{
    public:
        QVariant operator()(const QString &);
        QVariant operator()(const QVariantMap &);

    private:
        QVariant copyText(const QString &);
        QVariant copyImage(const QString &);

};


}
