#pragma once 

#include "SyncWebView.hpp"


class JavascriptInvoker : private SyncWebView
{
    public:
        JavascriptInvoker();
        QVariant execute(const QString &);
};
