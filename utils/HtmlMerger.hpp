#pragma once 

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QWebSettings>
#include <QDirIterator>

#include "SyncWebView.hpp"
#include "utils.hpp"



class HtmlMerger : private SyncWebView
{
    public:
        HtmlMerger(const QString &file);

        void appendText(const QString &text);
        void appedScript(const QString &text);

        void appendFile(const QString &file);
        void appendTemplateFile(const QString &file);

        void appendFromDir(const QString &dir);
        void appendTemplatesFromDir(const QString &dir);

        QString getContent();

        void save();
        void saveTo(const QString &);

    private:
        QString escapeText(const QString &);
        QString getFileContent(const QString &);


    private:
        QString _path;

};
