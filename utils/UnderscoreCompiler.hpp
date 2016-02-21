#pragma once 

#include <QTextStream>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "JavascriptInvoker.hpp"


class UnderscoreCompiler
{
    public:

        bool compile(const QString &src, const QString &dest);
        bool compileFile(const QString &src, const QString &dest);

    private:
        JavascriptInvoker _invoker;
};
