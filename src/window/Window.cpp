
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>
#include <QAction>
#include <QDebug>
#include <QWebSettings>
#include <QWebInspector>
#include <QCoreApplication>
#include <QMessageBox>

namespace Xeth{

Window::Window(const Window &wnd) :
    _facade(wnd._facade),
    _contextBuilder(wnd._contextBuilder)
{}

Window::Window(Facade &facade) :
    _closing(false),
    _facade(facade),
    _contextBuilder(facade)
{
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    QWebInspector *inspector = new QWebInspector;
//    inspector->setPage(page());
//    inspector->show();

    _trayIcon = new Tray(this);
    QObject::connect(page()->mainFrame(), &QWebFrame::loadFinished, this, &Window::loadTemplates);
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(initObjects()));
    setContextMenuPolicy(Qt::NoContextMenu);
    setFixedSize(960, 600);
    setUrl("qrc:/html/index.html");
    _trayIcon->hide();
    setIcon(":/icon/ethereum.ico");

//    _trayIcon->setToolTip("Ethereum Wallet");
    _trayMenu = new QMenu(this);
    _trayMenu->addSeparator();

    _activateAction = _trayMenu->addAction("hide");
    QObject::connect(_activateAction, &QAction::triggered, this, &Window::toggle);

    _trayMenu->addSeparator();

    _quitAction = _trayMenu->addAction("quit");
    QObject::connect(_quitAction, &QAction::triggered, this, &Window::close);

    _trayIcon->setContextMenu(_trayMenu);

    initConfig();

}

void Window::initConfig()
{
    initConfigOpt("tray", _showTrayOpt, true);
    initConfigOpt("tray_minimize", _minimizeToTrayOpt, false);
    initConfigOpt("tray_close", _closeToTrayOpt, false);
    QObject::connect(&_facade.getConfig(), &ConfigFacade::Change, this, &Window::updateConfig);
    if(_showTrayOpt)
    {
        showTray();
    }
}

void Window::updateConfig(const QString &key, const QString &value)
{
    try
    {
        if(key=="tray")
        {
            _showTrayOpt = value.toUInt() > 0;
            if(_showTrayOpt)
            {
                showTray();
            }
            else
            {
                hideTray();
            }
        }
        else
        if(key=="tray_minimize")
        {
            _minimizeToTrayOpt = value.toUInt() > 0;
        }
        else
        if(key=="tray_close")
        {
            _closeToTrayOpt = value.toUInt() > 0;
        }
    }
    catch(...)
    {}
}

void Window::initConfigOpt(const char *name, bool &opt, bool defaultVal)
{
    try
    {
        ConfigFacade & config = _facade.getConfig();
        QString trayConf = config.get(name).toString();
        if(!trayConf.length())
        {
            opt = defaultVal;
            QVariantMap request;
            request["name"] = name;
            request["value"] = defaultVal?"1":"0";
            config.set(request);
        }
        else
        {
            opt = trayConf.toUInt() > 0;
        }
    }
    catch(...)
    {
        opt = defaultVal;
    }
}


void Window::showTray()
{
    _trayIcon->setVisible(true);
    QObject::connect(&_facade.getWallet(), &WalletFacade::Transaction, this, &Window::notifyTransaction);
}

void Window::hideTray()
{
    _trayIcon->setVisible(false);
    QObject::disconnect(&_facade.getWallet(), &WalletFacade::Transaction, this, &Window::notifyTransaction);
}

void Window::toggle()
{
    if(isVisible())
    {
        _activateAction->setText("show");
        hide();
    }
    else
    {
        _activateAction->setText("hide");
        setWindowState(Qt::WindowActive);
        show();
        activateWindow();
    }
}

void Window::close()
{
    _closing = true;
    QWebView::close();
    QMessageBox * msgBox = new QMessageBox(this);
    msgBox->setText("Xeth shutting down ...");
    msgBox->setStandardButtons(0);
    msgBox->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    msgBox->show();
    hideTray();
    QTimer::singleShot(100, this, SLOT(emitClosing()));
//    QTimer::singleShot(100, msgBox, SLOT(close()));
}


void Window::emitClosing()
{
    emit Closing();
}

void Window::changeEvent(QEvent* event)
{
    if(_showTrayOpt && _minimizeToTrayOpt && event->type() == QEvent::WindowStateChange && this->windowState() & Qt::WindowMinimized)
    {
        _activateAction->setText("show");
        QTimer::singleShot(250, this, SLOT(hide()));
        event->ignore();
    }
    else
    {
        QWebView::changeEvent(event);
    }
}


void Window::closeEvent(QCloseEvent *event)
{
    if(!_closing && _showTrayOpt && _closeToTrayOpt)
    {
        _activateAction->setText("show");
        QTimer::singleShot(250, this, SLOT(hide()));
        event->ignore();
    }
}

void Window::notifyTransaction(const QVariantMap &tx)
{
    QString amount = tx["amount"].toString();
    if(amount!="0")
    {
        _trayIcon->showMessage(tx["category"].toString(), _facade.getConverter().fromWei(amount).toString());
    }
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
//    _trayIcon->setIcon(icon);
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
    moveToScreenCenter(*this);
}


void Window::moveToScreenCenter(QWebView &view)
{
    QRect rect = view.geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    view.setGeometry(rect);
}


}
