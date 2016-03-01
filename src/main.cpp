#include <QList>
#include <QString>
#include <QApplication>

#include <QDebug>

#include <stdexcept>
#include <iostream>

#include "Application.hpp"


int main(int argc, char* argv[])
{
    try
    {
        Xeth::Settings settings;
        settings.readCommandLineArgs(argc, argv);

        Xeth::Application app(settings, argc, argv);
        return app.exec();
    }
    catch(const std::exception &e)
    {
        std::cerr<<"exception : "<<e.what()<<std::endl<<std::flush;
        return 1;
    }
}

