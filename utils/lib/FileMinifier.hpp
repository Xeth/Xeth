#pragma once 

#include "JavascriptInvoker.hpp"
#include "FileParser.hpp"


class WhitespaceRemover
{
    public:
        QString operator()(const QString &);

};


typedef FileParser<WhitespaceRemover> FileMinifier;


