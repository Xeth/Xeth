#pragma once 

#include <QWebView>
#include <QApplication>
#include <QWebFrame>


class SyncWebView
{
    public:
        SyncWebView(const QUrl &);

        QWebView & getHandle();

    private:
        QWebView _handle;
};
