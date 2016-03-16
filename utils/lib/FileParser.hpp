#pragma once 

#include <QTextStream>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "JavascriptInvoker.hpp"


template<class Parser>
class FileParser
{
    public:

        FileParser();
        FileParser(const Parser &);

        bool parseDirectory(const QString &src, const QString &dest);
        bool parse(const QString &src, const QString &dest);

    private:
        Parser _parser;
};


#include "FileParser.ipp"
