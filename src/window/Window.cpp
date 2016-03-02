
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>
#include <QAction>
#include <QDebug>
#include <QWebSettings>
#include <QWebInspector>

namespace Xeth{


Window::Window(FrameContextBuilder &contextBuilder) :
    _contextBuilder(contextBuilder)
{
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    QWebInspector *inspector = new QWebInspector;
//    inspector->setPage(page());
//    inspector->show();
    QObject::connect(page()->mainFrame(), &QWebFrame::loadFinished, this, &Window::loadTemplates);
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(initObjects()));
    setContextMenuPolicy(Qt::NoContextMenu);
    setFixedSize(960, 600);
    setUrl("qrc:/index.html");
    setIcon(":/icon/ethereum.ico");

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


void Window::initObjects()
{
    _contextBuilder.buildContext(page()->mainFrame());
}


void Window::loadTemplates()
{
    QDirIterator it(":/template", QDir::Files);
    page()->mainFrame()->evaluateJavaScript("var XETH_templates = new TemplateRegistry;");
    while(it.hasNext())
    {
        QFileInfo info(it.next());
        QString name = info.baseName();
        QFile file(info.filePath());

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            throw std::runtime_error("failed to read file");
        }

        QTextStream stream(&file);
        QString content = stream.readAll();

        QString js = "XETH_templates.register('";
        js+=name;
        js+="',";
        js+=content;
        js+=");";
        qDebug()<<"registering template "<<name<<" : "<<page()->mainFrame()->evaluateJavaScript(js);
        file.close();
    }
}



void Window::moveToScreenCenter()
{
    QRect rect = geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(rect);
}



}
