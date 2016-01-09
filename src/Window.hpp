#pragma once

#include <QWebView>
#include <QDebug>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

#include "FrameContextBuilder.hpp"

namespace Xeth{

class Window : public QWebView
{
    Q_OBJECT
    
    public:
        explicit Window(const char *, FrameContextBuilder &contextBuilder);

        void moveToScreenCenter();

    protected:
        void javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID );


    private slots:
        void addJSObject();

    private:
        FrameContextBuilder &_contextBuilder;

};

}
