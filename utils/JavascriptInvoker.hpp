#pragma once 

#include <QWebView>
#include <QApplication>
#include <QWebFrame>


class JavascriptInvoker
{
    public:
        JavascriptInvoker();
        QVariant execute(const QString &);

    private:
        QWebView _window;
};
