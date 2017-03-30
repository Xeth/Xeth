#pragma once 

#include <QTextStream>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "JavascriptInvoker.hpp"


class NullFileFilter
{
    public:
        bool operator ()(const QFileInfo &) const;
};



class FileExtensionFilter
{
    public:
        FileExtensionFilter(const QString &);
        bool operator()(const QFileInfo &) const;

    private:
        QString _extension;
};


template<class Parser, class FileFilter=NullFileFilter>
class FileParser
{
    public:

        FileParser();
        FileParser(const Parser &);
        FileParser(const FileFilter &);
        FileParser(const Parser &, const FileFilter &);


        bool parseDirectory(const QString &src, const QString &dest);
        bool parse(const QString &src, const QString &dest);

    private:
        Parser _parser;
        FileFilter _filter;
};


#include "FileParser.ipp"
