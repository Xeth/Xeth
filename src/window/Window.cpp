
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>
#include <QAction>

namespace Xeth{

Window::Window(FrameContextBuilder &contextBuilder) :
    _contextBuilder(contextBuilder)
{

    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));
//    new QAction(QIcon("qrc:/img/eth.png"), tr("ETH"), this);

}

void Window::setUrl(const char *uri)
{
    QUrl url(uri);
    QWebView::setUrl(url);
}

void Window::setIcon(const char *uri)
{
    setWindowIcon(QIcon(uri));
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
