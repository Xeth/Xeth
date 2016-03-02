#include "JavascriptInvoker.hpp"


JavascriptInvoker::JavascriptInvoker() :
    SyncWebView(QUrl("qrc:/index.html"))
{}



QVariant JavascriptInvoker::execute(const QString &js)
{
    return getHandle().page()->mainFrame()->evaluateJavaScript(js);
}
