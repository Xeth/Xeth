#include "SyncWebView.hpp"
#include <QDebug>

SyncWebView::SyncWebView(const QUrl &url)
{
    qDebug()<<"opening  : "<<url;
    _handle.setUrl(url);
    QEventLoop pause;
    QObject::connect(_handle.page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), &pause,  SLOT(quit()));
    pause.exec();
    qDebug()<<"opened";
}



QWebView & SyncWebView::getHandle()
{
    return _handle;
}
