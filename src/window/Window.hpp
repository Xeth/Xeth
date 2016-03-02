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


#include "FrameContextBuilder.hpp"


namespace Xeth{


class Window : public QWebView
{
    Q_OBJECT
    
    public:
        explicit Window(FrameContextBuilder &contextBuilder);

        void moveToScreenCenter();


    protected:
        void javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID );
        void setUrl(const char *);
        void setIcon(const char *);

    private slots:
        void initObjects();
        void loadTemplates();

    private:
        FrameContextBuilder &_contextBuilder;

};

}
