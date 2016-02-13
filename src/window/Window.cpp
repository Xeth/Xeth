
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>

namespace Xeth{

Window::Window(const char *uri, FrameContextBuilder &contextBuilder) :
    _contextBuilder(contextBuilder)
{

    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));
    QUrl startURL(uri);

    setUrl(startURL);
}


void Window::javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID )
{
    qDebug()<<message<<lineNumber<<sourceID;
}


void Window::addJSObject()
{
    _contextBuilder.buildContext(page()->mainFrame());
}


void Window::moveToScreenCenter()
{
    QRect rect = geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(rect);
}



}
