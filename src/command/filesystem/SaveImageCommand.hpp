#pragma once

#include <QVariant>
#include <QVariantMap>
#include <QString>
#include <QWebElement>
#include <QImage>
#include <QPainter>
#include <QApplication>
//#include <QWidget>
#include <QWebView>
#include <QWebFrame>


namespace Xeth{


class SaveImageCommand 
{
    public:
        QVariant operator()(const QVariantMap &);

    private:
        QVariant saveImage(const QString &, const QString &);
};


}
