#pragma once 

#include "JavascriptInvoker.hpp"
#include "FileParser.hpp"


class MinifyCSS
{
    public:
        QString operator()(const QString &);

};


typedef FileParser<MinifyCSS> CSSMinifier;


