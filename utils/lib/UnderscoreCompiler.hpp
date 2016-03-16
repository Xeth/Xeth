#pragma once 

#include "JavascriptInvoker.hpp"
#include "FileParser.hpp"

class UnderscoreParser
{
    public:
        QString operator()(const QString &);

    private:
        JavascriptInvoker _invoker;
};


typedef FileParser<UnderscoreParser> UnderscoreCompiler;


