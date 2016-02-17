#include "SaveImageCommand.hpp"
#include <QDebug>

namespace Xeth{


QVariant SaveImageCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("selector")||!request.contains("file"))
    {
        qDebug()<<"invalid arguments : selector="<<request.contains("selector")<<" file="<<request.contains("file");
        return QVariant::fromValue(false);
    }

//    QWebElement element  = request["image"].value<QWebElement>();
    return saveImage(request["selector"].toString(), request["file"].toString());
}


QVariant SaveImageCommand::saveImage(const QString &selector, const QString &path)
{
    qDebug()<<"saving "<<selector;
    QWebView view(QApplication::activeWindow());
    QWebElement element = view.page()->mainFrame()->findFirstElement(selector);
    QImage image(element.geometry().width(), element.geometry().height(), QImage::Format_ARGB32);
    QPainter painter(&image);
    element.render(&painter);
    painter.end();
    return QVariant::fromValue(image.save(path));
}

}
