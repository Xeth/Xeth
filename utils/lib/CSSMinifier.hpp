#pragma once 

#include "JavascriptInvoker.hpp"
#include "FileParser.hpp"


class MinifyCSS
{
    public:
        QString operator()(const QString &);

};


class CSSMinifier : public FileParser<MinifyCSS, FileExtensionFilter>
{
    public:
        CSSMinifier();
};

