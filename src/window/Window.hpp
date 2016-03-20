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


#include "facade/Facade.hpp"
#include "FrameContextBuilder.hpp"


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

    private slots:
        void initObjects();
        void loadTemplates();
        void toggle();
        void notifyTransaction(const QVariantMap &);

    private:
        FrameContextBuilder _contextBuilder;
        ConverterFacade &_converter;
        QSystemTrayIcon *_trayIcon;
        QMenu *_trayMenu;

};

}
