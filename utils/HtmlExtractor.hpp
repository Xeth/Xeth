#pragma once 

#include <QString>
#include <QDir>
#include <QWebElement>
#include <QWebFrame>
#include <QRegularExpression>

#include "SyncWebView.hpp"
#include "utils.hpp"


class HtmlExtractor : public SyncWebView
{
    public:
        HtmlExtractor(const QString &path);

        void move(const QString &selector, const QString &file, bool outer=true);

        void moveTemplates(const QString &dir);

        QString getContent();
        void save();
        void saveTo(const QString &path);

    private:
        QWebElement getDocument();
        QWebElement find(const QString &selector);
        void move(QWebElement &, const QString &path, bool outer=true);
        void writeFile(const QString &path, const QString &content);

    private:
        QString _path;

};
