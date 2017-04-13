#pragma once 

#include <QApplication>


#include "conf/Settings.hpp"
#include "facade/Facade.hpp"
#include "window/Window.hpp"


namespace Xeth{



class Application : public QObject
{
    Q_OBJECT

    public:
        Application(Settings &, int &argc, char **argv);
        int exec();
        Window & getWindow();

    private:


    private slots:
        void shutdown();

    private:
        QApplication _app;
        Facade _facade;
        Window _window;
};


}
