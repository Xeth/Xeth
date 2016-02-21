#include "JavascriptInvoker.hpp"


JavascriptInvoker::JavascriptInvoker()
{
    QUrl url("qrc:/index.html");
    _window.setUrl(url);
    QEventLoop pause;
    QObject::connect(_window.page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), &pause,  SLOT(quit()));
    pause.exec();
}



QVariant JavascriptInvoker::execute(const QString &js)
{
    return _window.page()->mainFrame()->evaluateJavaScript(js);
}
