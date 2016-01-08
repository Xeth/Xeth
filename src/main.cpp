#include <QList>
#include <QString>
#include <QApplication>

#include <QDebug>

#include "Application.hpp"


int main(int argc, char* argv[])
{
    Xeth::Settings settings;
    settings.readCommandLineArgs(argc, argv);

    Xeth::Application app(settings, argc, argv);
    return app.exec();
}

