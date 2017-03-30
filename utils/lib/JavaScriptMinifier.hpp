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


class JavascriptMinifier : public FileParser<MinifyJS, FileExtensionFilter>
{
    public:
        JavascriptMinifier();
};

