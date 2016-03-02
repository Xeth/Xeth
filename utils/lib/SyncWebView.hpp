#pragma once 

#include <QWebView>
#include <QApplication>
#include <QWebFrame>
#include <QWebSettings>


class SyncWebView
{
    public:
        SyncWebView();
        SyncWebView(const QUrl &);

        void open(const QUrl &);

        void disableJavaScript();
        void endableJavaScript();
        void setJavaScriptEnabled(bool enabled);

        QWebView & getHandle();

    private:
        QWebView _handle;
        bool _javscriptEnabled;
};
