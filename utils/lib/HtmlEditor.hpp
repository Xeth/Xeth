#pragma once 

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QWebSettings>
#include <QDirIterator>
#include <QWebElement>
#include <QDir>
#include <QWebFrame>
#include <QRegularExpression>

#include "SyncWebView.hpp"
#include "utils.hpp"
#include "utils.hpp"



class HtmlEditor : public SyncWebView
{
    public:
        HtmlEditor(const QString &file);

        void appendTo(const QString &el, const QString &text, bool outer=false);
        void prependTo(const QString &el, const QString &text, bool outer=false);

        void appendToHeader(const QString &text);
        void prependToHeader(const QString &text);

        void appendToBody(const QString &text, bool outer=false);
        void prependToBody(const QString &text, bool outer=false);

        QWebElement remove(const QString &el);
        QWebElementCollection removeAll(const QString &el);

        QWebElement getDocument();
        QWebElement find(const QString &selector);
        QString getContent();

        void save();
        void saveTo(const QString &);

    private:
        void forceInsert(const QString &regex, const QString &text, bool insertBefore = true);

    private:
        QString _path;
};
