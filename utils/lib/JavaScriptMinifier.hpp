#pragma once 

#include "JavascriptInvoker.hpp"
#include "FileParser.hpp"


class MinifyJS
{
    public:
        QString operator()(const QString &);

    private:
        JavascriptInvoker _invoker;

};


typedef FileParser<MinifyJS> JavascriptMinifier;


