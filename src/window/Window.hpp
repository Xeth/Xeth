#pragma once

#include <QWebView>
#include <QDebug>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextStream>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QSystemTrayIcon>
#include <QCoreApplication>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>


#include "facade/Facade.hpp"
#include "FrameContextBuilder.hpp"
#include "Tray.hpp"


namespace Xeth{


class Window : public QWebView
{
    Q_OBJECT
    
    public:
        explicit Window(Facade &facade);

        void moveToScreenCenter();

    protected:
        void javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID );
        void setUrl(const char *);
        void setIcon(const char *);


    private:
        Window(const Window &);
        void showTray();
        void hideTray();
        void initConfig();
        void initConfigOpt(const char *, bool &, bool);

    private slots:
        void close();
        void initObjects();
        void loadTemplates();
        void toggle();
        void notifyTransaction(const QVariantMap &);
        void changeEvent(QEvent* );
        void closeEvent(QCloseEvent *event);
        void updateConfig(const QString &key, const QString &value);

    private:
        bool _showTrayOpt;
        bool _minimizeToTrayOpt;
        bool _closeToTrayOpt;
        bool _closing;
        Facade &_facade;
        FrameContextBuilder _contextBuilder;
        Tray *_trayIcon;
        QMenu *_trayMenu;
        QAction *_activateAction;
        QAction *_quitAction;

};

}
