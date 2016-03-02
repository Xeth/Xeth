#include "SyncWebView.hpp"


SyncWebView::SyncWebView() :
    _javscriptEnabled(true)
{}


SyncWebView::SyncWebView(const QUrl &url) : 
    _javscriptEnabled(true)
{
    open(url);
}


void SyncWebView::open(const QUrl &url)
{
    QEventLoop pause;
    if(_javscriptEnabled)
    {
        QObject::connect(_handle.page()->mainFrame(), &QWebFrame::javaScriptWindowObjectCleared, &pause,  &QEventLoop::quit);
    }
    else
    {
        QObject::connect(_handle.page()->mainFrame(), &QWebFrame::loadFinished, &pause,  &QEventLoop::quit);
    }
    _handle.setUrl(url);
    pause.exec();
}


void SyncWebView::endableJavaScript()
{
    setJavaScriptEnabled(true);
}


void SyncWebView::disableJavaScript()
{
    setJavaScriptEnabled(false);
}


void SyncWebView::setJavaScriptEnabled(bool enabled)
{
    _javscriptEnabled = enabled;
    QWebSettings * settings = getHandle().settings();
    settings->setAttribute(QWebSettings::JavascriptEnabled, false);
}


QWebView & SyncWebView::getHandle()
{
    return _handle;
}
