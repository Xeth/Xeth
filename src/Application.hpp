#pragma once 

#include <QApplication>


#include "Settings.hpp"
#include "facade/Facade.hpp"
#include "window/FrameContextBuilder.hpp"
#include "window/Window.hpp"


namespace Xeth{


class Application : public QObject
{
    Q_OBJECT

    public:
        Application(const Settings &, int &argc, char **argv);
        int exec();


    private:
        QApplication _app;
        Facade _facade;
        FrameContextBuilder _contextBuilder;
        Window _window;
};

}
