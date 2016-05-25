#include "Application.hpp"

#ifdef __WINDOWS_OS__
#include <windows.h>
#else
#include <signal.h>
#endif

#include <boost/bind.hpp>

namespace Xeth{


//Ugly, use lambda instead
Application * g_App;

#ifdef __WINDOWS_OS__
BOOL WINAPI SignalHandler(DWORD type)
{
    switch(type)
    {
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
#else
void SignalHandler(int)
{
#endif

    g_App->getWindow().close();
#ifdef __WINDOWS_OS__
    default: 
        break;
    }
    return true;
#endif

}


Application::Application(const Settings &settings, int &argc, char **argv):
    _app(argc, argv),
    _facade(settings),
    _window(_facade)
{}


Window & Application::getWindow()
{
    return _window;
}

int Application::exec()
{
    _window.moveToScreenCenter();
    _window.show();
    QObject::connect(&_window, SIGNAL(Closing()), this, SLOT(shutdown()), Qt::DirectConnection);

    g_App = this;

#ifdef __WINDOWS_OS__
    SetConsoleCtrlHandler(SignalHandler, true);
#else
    signal(SIGINT, SignalHandler);

#endif

    return _app.exec();
}


void Application::shutdown()
{
    _facade.shutdown();
    QCoreApplication::exit();
}


}
