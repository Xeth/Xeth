
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>
#include <QAction>
#include <QDebug>
#include <QWebSettings>
#include <QWebInspector>
#include <QCoreApplication>

namespace Xeth{

Window::Window(const Window &wnd) :
    _contextBuilder(wnd._contextBuilder),
    _converter(wnd._converter)
{}

Window::Window(Facade &facade) :
    _contextBuilder(facade),
    _converter(facade.getConverter())
{
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    QWebInspector *inspector = new QWebInspector;
//    inspector->setPage(page());
//    inspector->show();

    _trayIcon = new QSystemTrayIcon(this);
    QObject::connect(page()->mainFrame(), &QWebFrame::loadFinished, this, &Window::loadTemplates);
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(initObjects()));
    setContextMenuPolicy(Qt::NoContextMenu);
    setFixedSize(960, 600);
    setUrl("qrc:/index.html");
    _trayIcon->hide();
    setIcon(":/icon/ethereum.ico");

    _trayIcon->setToolTip("Ethereum Wallet");
    _trayMenu = new QMenu(this);
    _trayMenu->addSeparator();

    QAction *activate = _trayMenu->addAction("activate");
    QObject::connect(activate, &QAction::triggered, this, &Window::toggle);

    _trayMenu->addSeparator();

    QAction *quit = _trayMenu->addAction("quit");
    QObject::connect(quit, &QAction::triggered, this, &Window::close);

    _trayIcon->setContextMenu(_trayMenu);
    _trayIcon->setVisible(true);

    QObject::connect(&facade.getNotifier(), &Notifier::Transaction, this, &Window::notifyTransaction);

}



void Window::toggle()
{
    if(isVisible())
    {
        hide();
    }
    else
    {
        showNormal();
    }
}


void Window::notifyTransaction(const QVariantMap &tx)
{
    _trayIcon->showMessage(tx["category"].toString(), _converter.fromWei(tx["amount"]).toString());
}

void Window::setUrl(const char *uri)
{
    QUrl url(uri);
    QWebView::setUrl(url);
}

void Window::setIcon(const char *uri)
{
    QIcon icon(uri);
    setWindowIcon(icon);
    _trayIcon->setIcon(icon);
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
