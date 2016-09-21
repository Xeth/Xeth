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
        settings.readConfigFile();
        settings.readCommandLineArgs(argc, argv);

        if(settings.has("version"))
        {
            std::cout<<"Version: 0.3.1 (BETA)"<<std::endl;
            return 0;
        }

        if(settings.has("help"))
        {
            std::cout<<"--testnet         | to run on testnet"<<std::endl;
            std::cout<<"--fast            | to synchronize in fast mode, by default is 1"<<std::endl;
            std::cout<<"--dao-fork=[1|0]  | enable/disable dao hard fork, by default dao-fork is 1"<<std::endl;
            std::cout<<"--version         | Xeth version"<<std::endl;
            return 0;
        }

        Xeth::Application app(settings, argc, argv);
        return app.exec();
    }
    catch(const std::exception &e)
    {
        std::cerr<<"exception : "<<e.what()<<std::endl<<std::flush;
        return 1;
    }
}

